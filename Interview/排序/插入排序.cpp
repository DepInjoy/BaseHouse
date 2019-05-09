#include <iostream>
#include <string>

template<typename T>
void swap(T& v1, T& v2){
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

/*
	类似于摸牌过程，每次摸到的牌按照大小排序
*/
template<typename T, int N>
void Insertion_Sort(T (&list)[N], int N)
{
	if (!list || N <= 0) return;

	int j = 0;
	for (int i = 0; i < N; i++){
		//摸一张牌
		T tmp = list[i];
		for (j = i; (j > 0) && (list[j - 1] > tmp); j--)
			list[j] = list[j - 1];		//移出空位
		list[j] = tmp;					//将新摸到的牌归位
	}
}

int main(int argc, char *argv[])
{
	//测试项1
	int a0[10] = { 5, 4, 6, 8, 9, 2, 3, 1, 7, 0 };
	Insertion_Sort(a0, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a0[i] << " ";
	}
	std::cout << std::endl;
	
	//测试项2
	int a1[10] = { 9,8,7,6,5,4,3,2,1,0 };
	Insertion_Sort(a1, 10);
	for (int i = 0; i < 10; i++){
		std::cout << a1[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}