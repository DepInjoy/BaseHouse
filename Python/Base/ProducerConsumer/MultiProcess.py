import random
import time
from multiprocessing import Process, Queue, Event

class Producer(Process):
    def __init__(self, queue, event):
        super().__init__()
        self._queue = queue
        self._event = event

    def run(self):
        while True:
            try:
                item = random.randint(1, 100)
                '''
                block=True ,如果当前队列已经满了,则put()使调用线程暂停,直到空出一个数据单元
                block=False,如果当前队列已经满了,则put()将引发Full异常。
                block默认为True
                '''
                if not self._queue.full():
                    self._queue.put(item, block=False)
                    self._event.set()
                    print('Produce ', item)
                else:
                    self._event.set()
                    print("Queue is full")
            except Queue.Full:
                print("Queue is full")
            time.sleep(1.0e-4)

class Consumer(Process):
    def __init__(self, queue, event):
        super().__init__()
        self._queue = queue
        self._event = event

    def run(self):
        while True:
            if not self._event.is_set():
                continue
            if not self._queue.empty():
                item = self._queue.get()
                print('Consume ', item)
            else:
                self._event.clear()
                print("Queue is empty， please wait!")
            self._event.wait()
            time.sleep(1.0e-4)

if __name__ == '__main__':
    q = Queue(maxsize=100)
    event = Event()
    producer = Producer(q, event)
    consumer = Consumer(q, event)
    producer.start()
    consumer.start()
