#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T>& vec) {
	// iterator�� std::vecotr<T>�� ���� Ÿ��
	// ����Ÿ��: �����Ϸ����� � Ű����� typedef�� �����ǵ� type�̶�� ���� �˷��ֱ� ���� typename�̶�� Ű���带 ����ؾ���
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
	for (const auto &elem : vec) {
		std::cout << "����: " << elem << std::endl;
	}
}

int main() {
	// vec.begin() // ���� ������ �ּ� ��ȯ
	// vec.end() // ������ ���� + 1�� �ּ� ��ȯ, ���� ������ ���� ������ ���� *(vec.end() - 1)�� �����ؾ���
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "ó�� ���� ����" << std::endl;
	print_vector(vec);
	std::cout << "-----------------------" << std::endl;

	// vec[2] �տ� 15 �߰�
	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);
	std::cout << "-----------------------" << std::endl;


	// vec[3] ����
	vec.erase(vec.begin() + 3);
	print_vector(vec);
	std::cout << "-----range-based for ��-----" << std::endl;
	print_vector_range_based(vec);
}