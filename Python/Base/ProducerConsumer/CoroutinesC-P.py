import random

'''
    消费者向生产者请求数据
'''
def consumer(p):
    p.send(None)
    while True:
        item = random.randint(1, 100)
        print('Consume ', item)
        p.send(item)

def producer():
    while True:
        item = yield
        print("Prodece ", item)

if __name__ == '__main__':
    p = producer()
    consumer(p)
