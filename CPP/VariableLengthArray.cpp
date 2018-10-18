#include <iostream>
class CArray{
	int size;
	int* ptr;
public:
	CArray(int s = 0);
	CArray(CArray& a);
	~CArray();
	int length()	{ return size; }
	void push_back(int a);
	int& operator[](int i);
	CArray& operator=(const CArray& a);
};

CArray::CArray(int s)
	:size(s)
{
	s == 0 ? (ptr = NULL) : (ptr = new int[s]);
}

CArray::CArray(CArray& a)
	: size(0),
	ptr(NULL)
{
	if (a.ptr == NULL){
		ptr = NULL;
		size = 0;
		return;
	}
	ptr = new int[a.size];
	memcpy(ptr, a.ptr, a.size * sizeof(int));
	size = a.size;
}

CArray::~CArray()
{
	if (ptr)	delete[] ptr;
	size = 0;
}

CArray& CArray::operator=(const CArray& a)
{
	if (ptr == a.ptr)	//避免a=a的操作
		return *this;

	if (a.ptr == NULL){
		if (ptr) delete ptr;
		ptr = NULL;
		size = 0;
		return *this;
	}

	if (size < a.size){		//节约时间
		if(ptr) delete[] ptr;
		ptr = new int[a.size];
	}
	memcpy(ptr, a.ptr, a.size * sizeof(int));
	size = a.size;
	return * this;
}

int& CArray::operator[](int i)
{
	return ptr[i];
}


void CArray::push_back(int a)
{
#if 0
	if (ptr){
		int* tmp = new int[size + 1];
		memcpy(tmp, ptr, sizeof(int)*size);
		delete ptr;
		ptr = tmp;
	}
	else
		ptr = new int[1];
	ptr[size++] = a;
#endif
	//分配较大的控件来节约时间
	if (!ptr){
		ptr = new int[4];
	}else{
		if (size % 4 == 0){
			int* tmp = new int[4 * (size / 4 + 1)];
			memcpy(tmp, ptr, size * sizeof(int));
			delete ptr;
			ptr = tmp;
		}
	}
	ptr[size++] = a;
}

int main()
{
	CArray a;
	for (int i = 0; i < 5; i++)
		a.push_back(i);						//在数组尾部添加元素
	for (int i = 0; i < a.length(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;

	CArray a0, a1;
	a0 = a;									//赋值运算符重载
	for (int i = 0; i < a0.length(); i++)
		std::cout << a0[i] << " ";
	std::cout << std::endl;

	a0 = a1;								//空
	for (int i = 0; i < a0.length(); i++)
		std::cout << a0[i] << " ";
	std::cout << std::endl;

	a[3] = 100;
	CArray a2(a);							//输入为CArray的构造函数
	for (int i = 0; i < a2.length(); i++)
		std::cout << a2[i] << " ";
	std::cout << std::endl;

	system("pause");
	return 0;
}