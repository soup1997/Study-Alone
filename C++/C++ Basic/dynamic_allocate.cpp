#include <iostream>

typedef struct test {
	char name[20];
	int age;
	int height;
}test;

void main()
{
	//--------------------Allocate single value-----------------------
	int* a = new int; // int크기의 공간 할당, 주소값을 p에 집어넣음
	*a = 10;
	std::cout << 'a:' << *a << std::endl;
	delete a; // 동적할당된 메모리 주소 해제


	//--------------------Allocate array-----------------------
	int arr_size = 50;
	int* arr = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = i;
	}

	std::cout << arr[0] << " "<< arr[arr_size-1] << std::endl;
	delete[] arr;


	//--------------------Allocate structure-----------------------
	test *list[10];
	
	std::cout << list[0] << std::endl; // 초기화되지 않은 메모리
	
	list[0] = new test;
	list[0]->age = 50;
	strcpy_s(list[0]->name, "Hello");
	list[0]->height = 180;

	std::cout << list[0] << std::endl;
	std::cout << list[0]->age << std::endl;
	std::cout << list[0]->name << std::endl;
	std::cout << list[0]->height << std::endl;
	
	//std::cout << list[1]->age << std::endl; // 위치를 읽는 동안 액세스 위반이 발생했습니다..
}