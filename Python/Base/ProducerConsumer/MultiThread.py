import random
import time
from threading import Thread, Lock, Condition
from queue import Queue

class Producer(Thread):
    def __init__(self, queue, lock, condition):
        super().__init__()
        self._queue = queue
        self._lock = lock
        self._condition = condition

    def run(self):
        while True:
            with self._condition:                           # 获取或等待线程条件
                try:
                    item = random.randint(1, 100)
                    '''
                    block=True ,如果当前队列已经满了,则put()使调用线程暂停,直到空出一个数据单元
                    block=False,如果当前队列已经满了,则put()将引发Full异常。
                    block默认为True
                    '''
                    if not self._queue.full():
                        self._lock.acquire()
                        self._queue.put(item, block=False)
                        self._lock.release()
                        self._condition.wait()              # 等待
                        self._condition.notify()            # 通知
                        print('Produce ', item)
                    else:
                        self._condition.notify()
                        print("Queue is full")
                except Queue.Full:
                    print("Queue is full")
        time.sleep(1.0e-4)

class Consumer(Thread):
    def __init__(self, queue, lock, condition):
        super().__init__()
        self._queue = queue
        self._lock = lock
        self._condition = condition

    def run(self):
        while True:
            with self._condition:
                if not self._queue.empty():
                    self._lock.acquire()
                    item = self._queue.get()
                    self._lock.release()
                    self._condition.notify()
                    self._condition.wait()
                    print('Consume ', item)
                else:
                    print("Queue is empty， please wait!")
            time.sleep(1.0e-4)

if __name__ == '__main__':
    q = Queue(maxsize=20)
    lock = Lock()
    # 线程条件变量，实现线程调度
    condition = Condition()
    producer = Producer(q, lock, condition)
    consumer = Consumer(q, lock, condition)
    producer.start()
    consumer.start()
