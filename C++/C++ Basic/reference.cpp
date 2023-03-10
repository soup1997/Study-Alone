# include <iostream>

namespace test1 {
	int member1[] = { 1, 2, 3, 4, 5 };

	int sum(int x, int y)
	{
		std::cout << "x + y: " <<x + y << std::endl;
		return x + y;
	}
}

namespace test2 {
	int member2[] = { 1, 2, 3, 4, 5 };

	int sub(int x, int y)
	{
		std::cout <<"x - y:"<< x - y << std::endl;
		return x - y;
	}
}

int swap(int& x) // // swap value through reference, not pointer
{
	x = 2023132043;

	return 0;
}

void swap_arr(int(&ref)[3]) // swap array value through reference, not pointer
{
	ref[0] = 4;
	ref[1] = 5;
	ref[2] = 6;
}

int& function(int& a) // return reference 
{
	a = 2;
	return a;
}

void main()
{
	// -----------------Namespace--------------------------
	int res1 = 0, res2 = 0;
	res1 = test1::sum(3, 4);
	res2 = test2::sub(3, 4);


	// -----------------Call by reference--------------------------
	int original_val = 2017200039;
	std::cout << "Original Value:" << original_val << std::endl;

	swap(original_val);
	std::cout << "Swapped Value:" << original_val << std::endl;


	int original_arr[3] = { 1, 2, 3 };
	std::cout << "Original Array:" << original_arr[0] << original_arr[1] << original_arr[2] << std::endl;

	swap_arr(original_arr);
	std::cout << "Swapped Array:" << original_arr[0] << original_arr[1] << original_arr[2] << std::endl;


	int b = 2;
	int c = function(b);
	std::cout << "c:" << c << std::endl;
}