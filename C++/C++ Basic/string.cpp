#include <iostream>
#include <string>

int main() {
	// ǥ���̹Ƿ� std�ȿ� string�� ���ǵǾ� ����
	std::string s = "abc";
	std::string t = "def";
	std::string s2 = s;

	std::cout << s << "�� ����: " << s.length() << std::endl;
	std::cout << s << " �ڿ�" << t << " �� ���̸� :" << s + t << std::endl;

	if (s == s2) {
		std::cout << s << " �� " << s2 << " �� ����" << std::endl;
	}

	if (s != t) {
		std::cout << s << " �� " << t << " �� �ٸ���" << std::endl;
	}

	t.insert(3, "g");
	std::cout << "insert function: " << t << std::endl; // insert function: defg

	std::string replace = "ghijklmnop";
	t.replace(3, replace.length(), replace);
	std::cout << "replace function: " << t << std::endl; // insert function: defg

	t.erase(3); // erase(������ġ, �� ��ġ) �� ��ġ �������ҽ� �� ��ġ���� �ڵ����� �Ҵ�
	std::cout << "erase function: " << t << std::endl; // insert function: defg

	t.clear(); // ���ڿ� ����, NULL�� �ȴ�.
	std::cout << "clear function: " << t << std::endl; // insert function: defg
	
	return 0;
}