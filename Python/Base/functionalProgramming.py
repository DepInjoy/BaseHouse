from functools import reduce

a = [1, 2, 3, 8, 5, 6, 7]
'''
    功能测试：   lamda以声明方式创建函数
    函数功能：   计算两个数之和
'''
sum = lambda a, b : a + b
b = sum(2,3)
print(b)                                        # 5


'''
    功能测试一：  filter相当于过滤器。
                筛选中列表中符合条件的元素
    函数功能：   查找大于5的元素
'''
b = filter(lambda x : x > 5, a)
print(list(b))                                  # [8, 6, 7]


'''
    功能测试二： 列表解析和map函数相当于对序列中每个项依次执行函数。
                列表解析，虽然代码很短，但本质上还是for循环，Python的for循环效率不高
                map函数的效率更高，它循环命令的速度相当于C语言，用于逐一遍历
    函数功能：    序列中各项的平方
'''
b = map(lambda x:x**2, a)
print(list(b))                                # [1, 4, 9, 64, 25, 36, 49]
b0 = [x**2 for x in a]
print(b0)                                       # [1, 4, 9, 64, 25, 36, 49]

'''
    功能测试三：  reduce是对一个序列的每个项迭代调用函数
                 用于递归计算
    函数功能：    求1-4的阶乘
'''
b = reduce(lambda x, y : y * x,range(1, 5))     #24
print(b)

