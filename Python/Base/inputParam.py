
'''
测试一：修改不可更改对象
结果：
    Before id(a)={0} 1586359408
    Afetr 1 id(a)={0} 1586359408
    Afetr 2 id(a)={0} 1586359440
    1
'''

a = 1
print("Before id(a)={0}", id(a))
def fun(a):
    print("Afetr 1 id(a)={0}", id(a))
    a = 2
    print("Afetr 2 id(a)={0}", id(a))
fun(a)
print(a)

'''
测试二：更改可更改对象

结果：
    Before id(b)={0} 168344968
    After id(b)={0} 168344968
    [2]
'''
b = []
print("Before id(b)={0}", id(b))
def fun1(b):
    b.append(2)
    print("After id(b)={0}", id(b))
fun1(b)
print(b)