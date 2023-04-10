#include <iostream>
#include <typeinfo>

template <typename T, unsigned int N>
class Array {
	T data[N];

public:
	Array(T(&arr)[N]) {
		for (int i = 0; i < N; i++) {
			data[i] = arr[i];
		}
	}

	T* get_array() { return data; }

	unsigned int size() { return N;}

	void print_all() {
		for (int i = 0; i < N; i++) {
			std::cout << data[i] << " , ";
		}

		std::cout << std::endl;
	}
};

template <int N>
struct Int {
	static const int num = N;
};

template <typename T, typename U>
struct add {
	typedef Int<T::num + U::num> result;
};

template <int N>
struct Factorial {
	static const int result = N * (Factorial<N - 1>::result);
};

// 템플릿 특수화
template<>
struct Factorial<1> {
	static const int result = 1;
};


int main() {
	int arr[3] = { 1, 2, 3 };
	Array<int, 3> arr_w(arr);
	arr_w.print_all();

	typedef Int<1> one;
	typedef Int<2> two;
	typedef add<one, two>::result three;
	std::cout << "Addition result :" << three::num << std::endl;


	std::cout << "6! = 6*5*4*3*2*1 = " << Factorial<6>::result << std::endl;
}