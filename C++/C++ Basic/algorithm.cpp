#include <iostream>
#include <algorithm>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

template <typename T>
struct comp {
	bool operator()(const T& a, const T& b) const { return a > b; } // return���� false�̸� swap�Ѵ�.
};

void sorting() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);

	std::cout << "���� �� ----" << std::endl;
	print(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end());

	std::cout << "������ �� ���� �� ----" << std::endl;
	print(vec.begin(), vec.end());

	std::cout << "������ �� ���� �� ----" << std::endl;
	std::sort(vec.begin(), vec.end(), comp<int>());
	print(vec.begin(), vec.end());
}

template <typename Iter>
void print2(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}
void remove() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(3);
	vec.push_back(2);

	std::cout << "ó�� vec ���� -----" << std::endl;
	print2(vec.begin(), vec.end());

	std::cout << "���Ϳ��� ���� 3�� ���� ���� -----" << std::endl;
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	print2(vec.begin(), vec.end());
}

int main() {
	sorting();
	std::cout << std::endl;
	remove();
}