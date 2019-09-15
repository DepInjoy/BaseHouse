import random

'''
    生产者向消费者请求数据
'''
def consumer():
    while True:
        item = yield
        print('Consume ', item)

def producer(c):
    # 使生成器继续运行，并且传递的参数为yield的返回值
    c.send(None)
    while True:
        item = random.randint(1, 100)
        print('Produce ', item)
        c.send(item)

if __name__ == '__main__':
    c = consumer()
    producer(c)