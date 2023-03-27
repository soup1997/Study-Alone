#include <iostream>
#include <array>

// 타입이 아닌 템플릿 인자
template <typename T, int num = 120>
T add_num(T t) {
	return t + num;
}

// std::array <int, 5> 자체가 하나의 타입
template <typename T>
void print(const T& t) {
	for (int i = 0; i < t.size(); i++) {
		std::cout << t[i] << " ";
	}
	std::cout << std::endl;
}

enum Color {
	RED = 0,
	BLUE = 1,
	GREEN = 2
};

template <typename T>
struct Compare {
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};

template <typename T, typename Comp = Compare<T>>
T Min(T a, T b) {
	Comp comp;
	if (comp(a, b)) {
		return a;
	}
}

int main() {
	int x = 3;
	std::cout << "x : " << add_num<int, 5>(x) << std::endl; // 8
	std::cout << "x: " << add_num<int>(x) << std::endl; // 123


	std::array<int, 5> arr = { 1, 2, 3, 4, 5 }; // arr은 heap 영역에 동적할당되는 것이 아닌 int 5개를 가지는 메모리로 즉 스택영역에 할당된다.
	std::array<int, 7> arr2 = { 1, 2, 3, 4, 5, 6, 7 };
	std::array<int, 3> arr3 = { Color::RED, Color::BLUE, Color::GREEN };
	print(arr);
	print(arr2);
	print(arr3);


	int a = 3, b = 5;
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl; //  Min 3 , 5 :: 3

	std::string s1 = "abc", s2 = "def";
	std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2) << std::endl; // Min abc, def::abc
}