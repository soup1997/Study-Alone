#include <iostream>
#include <string>

template <typename T>
void print(T arg) {
	std::cout << arg << std::endl;
}

// typename 뒤에 ...은 template parameter pack
// 함수에 인자로오는 ...은 function parameter pack
// 둘의 차이점은 템플릿의 경우 타입 앞에 ..., 함수의 경우 타입 뒤에 ...
// 가변길이 템플릿은 항상 재귀 함수 형태로 구성해야 하기 때문에, 반드시 재귀 호출 종료를 위한 함수를 따로 만들어야 한다.
template <typename T, typename... Types> // 가변 길이 템플릿
void print(T arg, Types... args) {
	std::cout << arg << ", ";
	print(args...);
}

void print_main() {
	print(1, 3.1, "abc");
	print(1, 2, 3, 4, 5, 6, 7);
	std::cout << std::endl;
}

//가변 길이 템플릿을 이용하여 가변 문자열 합치기
//std::string의 + operator는 +를 할때마다 동적할당이 일어나므로 overhead가 큼
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
	// 먼저 합쳐질 문자열의 총 길이를 구한다.
	size_t total_size = GetStringSize(s, strs...);

	// reserve를 통해 미리 공간을 할당해 놓는다.
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