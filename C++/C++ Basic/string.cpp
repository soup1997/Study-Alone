#include <iostream>
#include <string>

int main() {
	// 표준이므로 std안에 string이 정의되어 있음
	std::string s = "abc";
	std::string t = "def";
	std::string s2 = s;

	std::cout << s << "의 길이: " << s.length() << std::endl;
	std::cout << s << " 뒤에" << t << " 를 붙이면 :" << s + t << std::endl;

	if (s == s2) {
		std::cout << s << " 와 " << s2 << " 는 같다" << std::endl;
	}

	if (s != t) {
		std::cout << s << " 와 " << t << " 는 다르다" << std::endl;
	}

	t.insert(3, "g");
	std::cout << "insert function: " << t << std::endl; // insert function: defg

	std::string replace = "ghijklmnop";
	t.replace(3, replace.length(), replace);
	std::cout << "replace function: " << t << std::endl; // insert function: defg

	t.erase(3); // erase(시작위치, 끝 위치) 끝 위치 지정안할시 끝 위치까지 자동으로 할당
	std::cout << "erase function: " << t << std::endl; // insert function: defg

	t.clear(); // 문자열 삭제, NULL이 된다.
	std::cout << "clear function: " << t << std::endl; // insert function: defg
	
	return 0;
}