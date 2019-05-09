#include <iostream>
#include <string>

template<typename T>
void swap(T& v1, T& v2){
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

template<typename T, int N>
void PercDown(T (&A)[N], int p, int N)
{
	/* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
	int Parent, Child;
	T X;

	X = A[p]; /* 取出根结点存放的值 */
	for (Parent = p; (Parent * 2 + 1)<N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child]<A[Child + 1]))
			Child++;  /* Child指向左右子结点的较大者 */
		if (X >= A[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}

template<typename T, int N>
void Heap_Sort(T(&A)[N], int N)
{ 
	/* 堆排序 */
	int i;
	for (i = N / 2 - 1; i >= 0; i--)/* 建立最大堆 */
		PercDown(A, i, N);

	for (i = N - 1; i>0; i--) {
		/* 删除最大堆顶 */
		swap(A[0], A[i]);
		PercDown(A, 0, i);
	}
}

int main(int argc, char *argv[])
{
	int a0[10] = { 5, 4, 6, 8, 9, 2, 3, 1, 7, 0 };
	Heap_Sort(a0, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a0[i] << " ";
	}
	std::cout << std::endl;

	int a1[10] = { 9,8,7,6,5,4,3,2,1,0 };
	Heap_Sort(a1, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a1[i] << " ";
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}