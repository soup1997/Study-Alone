#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
	for (auto itr = m.begin(); itr != m.end(); itr++) {
		std::cout << itr->first << " " << itr->second << std::endl;
	}
}

template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
	auto itr = m.find(key);
	if (itr != m.end()) {
		std::cout << key << " ---> " << itr->second << std::endl;
	}

	else {
		std::cout << key << "은(는) 목록에 없습니다." << std::endl;
	}
}

int main() {
	std::map<std::string, double> pitcher_list;

	pitcher_list.insert(std::make_pair("차우찬", 3.04));
	pitcher_list.insert(std::make_pair("장원준", 3.05));
	pitcher_list.insert(std::make_pair("헥터", 3.09));

	pitcher_list["니퍼트"] = 3.56;
	pitcher_list["박종훈"] = 3.76;
	pitcher_list["켈리"] = 3.90;

	print_map(pitcher_list);
	std::cout << "------------------------------" << std::endl;

	// [] 연산자는, 맵에 없는 키를 참조하게 되면, 자동으로 값의 디폴트 생성자를 호출해서 원소를 추가해버린다.
	// 원소에 대응되는 값을 바꾸고 싶다면 insert가 아닌 []연산자를 활용한다.
	std::cout << "박세웅 방어율은? :: " << pitcher_list["박세웅"] << std::endl;

	search_and_print(pitcher_list, std::string("오승환"));
	search_and_print(pitcher_list, std::string("류현진"));
}