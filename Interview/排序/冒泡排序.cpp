#include <iostream>
#include <string>

template<typename T>
void swap(T& v1, T& v2){
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

template<typename T, int N>
void Bubble_Sort(T (&list)[N], int N)
{
	if (!list || N <= 0) return;

	for (int i = N - 1; i >= 0; i--){
		//初始化交换标识符
		bool flag = false;
		/* 一趟冒泡 */
		for (int j = 0; j < i; j++){
			if (list[j] > list[j + 1]){
				swap(list[j], list[j + 1]);
				//发生交换
				flag = true;
			}
		}
		//全程无交换，排序完成
		if (!flag) break;
	}
}

int main(int argc, char *argv[])
{
	//测试项1
	int a0[10] = { 5, 4, 6, 8, 9, 2, 3, 1, 7, 0 };
	Bubble_Sort(a0, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a0[i] << " ";
	}
	std::cout << std::endl;

	//测试项2
	int a1[10] = { 9,8,7,6,5,4,3,2,1,0 };
	Bubble_Sort(a1, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a1[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}