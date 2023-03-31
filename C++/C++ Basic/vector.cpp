#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T>& vec) {
	// iterator는 std::vecotr<T>의 의존 타입
	// 의존타입: 컴파일러에게 어떤 키워드는 typedef로 재정의된 type이라는 것을 알려주기 위해 typename이라는 키워드를 사용해야함
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
	for (const auto &elem : vec) {
		std::cout << "원소: " << elem << std::endl;
	}
}

int main() {
	// vec.begin() // 시작 원소의 주소 반환
	// vec.end() // 마지막 원소 + 1의 주소 반환, 따라서 마지막 원소 접근할 때는 *(vec.end() - 1)로 접근해야함
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "처음 벡터 상태" << std::endl;
	print_vector(vec);
	std::cout << "-----------------------" << std::endl;

	// vec[2] 앞에 15 추가
	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);
	std::cout << "-----------------------" << std::endl;


	// vec[3] 제거
	vec.erase(vec.begin() + 3);
	print_vector(vec);
	std::cout << "-----range-based for 문-----" << std::endl;
	print_vector_range_based(vec);
}