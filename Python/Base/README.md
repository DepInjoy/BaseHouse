### Python自省
运行时能够获得对象的类型.比如type(),dir(),getattr(),hasattr(),isinstance()
### Python函数的参数传递

Python中的类型是属于对象的，而非变量，Python中的对象有两种：<br/>
- 可更改(mutable)对象,包含int、float、strings, tuples、numbers等等。
- 不可更改(immutable)对象，包含list、dict等等。

程序示例
- inputParam.py<br/>
    功能说明：通过修改可更改对象和不可更改对象两个测试用例展示两者的不同。
    
### 数据结构
- List(列表)：序列结构，可以被修改
- Tuples(元组)：序列结构，不可以被修改；
- Dict(字典)
- Set(集合)：元素不重合且无序，不支持索引。
程序示例
- DataStruct.py<br/>
展示了使用过程中需要重点关注的几个知识点

### 函数式编程
主要由lamda()、map()、reduce() filter() 等几个函数组成。
程序示例：
- functionalProgramming.py<br/>
    功能说明：通过示例展示lamda、map、reduce、filter的使用。
	
### 生产者消费者模型实现
- ProducerConsumer
	- MultiThread.py   多线程实现
	- MultiProcess.py  多进程实现
	- CoroutinesC-P.py 协程实现，利用生成器实现，消费者向生产者请求数据
	- CoroutinesP-C.py 协程实现，利用生成器实现，生产者向消费者请求数据
