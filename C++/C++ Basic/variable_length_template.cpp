#include <iostream>
#include <string>

template <typename T>
void print(T arg) {
	std::cout << arg << std::endl;
}

// typename �ڿ� ...�� template parameter pack
// �Լ��� ���ڷο��� ...�� function parameter pack
// ���� �������� ���ø��� ��� Ÿ�� �տ� ..., �Լ��� ��� Ÿ�� �ڿ� ...
// �������� ���ø��� �׻� ��� �Լ� ���·� �����ؾ� �ϱ� ������, �ݵ�� ��� ȣ�� ���Ḧ ���� �Լ��� ���� ������ �Ѵ�.
template <typename T, typename... Types> // ���� ���� ���ø�
void print(T arg, Types... args) {
	std::cout << arg << ", ";
	print(args...);
}

void print_main() {
	print(1, 3.1, "abc");
	print(1, 2, 3, 4, 5, 6, 7);
	std::cout << std::endl;
}

//���� ���� ���ø��� �̿��Ͽ� ���� ���ڿ� ��ġ��
//std::string�� + operator�� +�� �Ҷ����� �����Ҵ��� �Ͼ�Ƿ� overhead�� ŭ
size_t GetStringSize(const char* s) { return strlen(s); }
size_t GetStringSize(const std::string& s) { return s.size(); }

template<typename String, typename... Strings>
size_t GetStringSize(const String& s, Strings... strs) {
	return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string* concat_str) { return; }

template<typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs) {
	concat_str->append(s);
	AppendToString(concat_str, strs...);
}


template<typename String, typename... Strings> 
std::string StrCat(const String& s, Strings... strs) {
	// ���� ������ ���ڿ��� �� ���̸� ���Ѵ�.
	size_t total_size = GetStringSize(s, strs...);

	// reserve�� ���� �̸� ������ �Ҵ��� ���´�.
	std::string concat_str;
	concat_str.reserve(total_size);

	concat_str = s;
	AppendToString(&concat_str, strs...);

	return concat_str;

}

void StrCat_main() {
	std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
	std::cout << std::endl;
}

int main() {
	print_main();
	StrCat_main();
}