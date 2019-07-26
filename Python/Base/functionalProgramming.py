from functools import reduce

a = [1, 2, 3, 8, 5, 6, 7]
'''
    功能测试：   lamda以声明方式创建函数
    函数功能：   计算两个数之和
'''
sum = lambda a, b : a + b
b = sum(2,3)
print(b)


'''
    功能测试一：  filter相当于过滤器，。
    函数功能：   查找大于5的元素
'''
b = filter(lambda x : x > 5, a)
print(list(b))


'''
    功能测试二：  map函数相当于对序列中每个项依次执行函数。
    函数功能：    序列中各项的平方
'''
b = map(lambda x:x**2, a)
print(list(b))


'''
    功能测试三：  reduce是对一个序列的每个项迭代调用函数
    函数功能：    求3的阶乘
'''
b = reduce(lambda x, y : y + x,range(1, 4))
print(b)

