#include <iostream>

class Marine {
private:
	static int total_marine_num; // 모든 인스턴스가 공유하는 하나의 static 변수
	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
	static void show_total_marine(); // 모든 인스턴스가 공유하는 하나의 static 함수

	~Marine();
};

// Static variable, method, initialization
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
	std::cout << "전체 마린 수: " << total_marine_num << std::endl;
}

// Initializer list
// 인스턴스 생성과 초기화를 동시에 수행
// reference 변수나, const 변수는 생성과 동시에 초기화가 수행되어야 함
// 따라서 초기화 리스트는 해당 변수들에 대해 특화된 방식이라 할 수 있다. 

Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	: coord_x(x), coord_y(y), hp(50), default_damage(default_damage), is_dead(false) {
	total_marine_num++;
}

Marine::~Marine() {
	total_marine_num--;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() {
	return default_damage;
}

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp < 0) is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine ***" << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) ";
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수: " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	Marine::show_total_marine();
}

int main() {
	Marine marine1(2, 3, 5);
	Marine::show_total_marine(); // 어떠한 객체도 이 함수를 소유하고 있지 않기 때문에 (클래스)::(static 함수)로 접근

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();

	create_marine();

	std::cout << std::endl << "마린 1이 마린 2를 공격 !" << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}