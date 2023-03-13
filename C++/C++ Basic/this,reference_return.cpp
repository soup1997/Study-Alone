// 자신을 가리키는 포인터 this
#include <iostream>

class Marine {
private:
	static int total_marine_num; // 모든 인스턴스가 공유하는 하나의 static 변수
	const static int i = 0; // const변수는 생성과 동시에 초기화 가능

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack() const; // 상수 멤버 함수, 다른 변수의 값을 바꾸지 않는 함수라고 명시하는 것
	
	Marine& be_attacked(int damage_earn); // 객체의 reference를 return
	Marine be_attacked2(int damage_earn); // reference를 return하는 것과 비교를 위한 임시 함수

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

/* 
Initializer list
인스턴스 생성과 초기화를 동시에 수행
reference 변수나, const 변수는 생성과 동시에 초기화가 수행되어야 함
따라서 초기화 리스트는 해당 변수들에 대해 특화된 방식이라 할 수 있다.
*/

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

int Marine::attack() const{
	return default_damage;
}

Marine& Marine::be_attacked(int damage_earn) {
	hp -= damage_earn; // this->hp = damage_earn;
	if (hp <= 0) is_dead = true; // if (this->hp <= 0) this->is_dead = true;

	return *this;
}

Marine Marine::be_attacked2(int damage_earn) {
	this->hp = damage_earn;
	if (this->hp <= 0) this->is_dead = true;

	return *this;
}

void Marine::show_status() {
	std::cout << " *** Marine ***" << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) ";
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수: " << total_marine_num << std::endl;
}

int main() {
	Marine marine1(2, 3, 5);
	marine1.show_status();

	Marine marine2(3, 5, 10);
	marine2.show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격 !" << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack()); // (marine2.be_attacked(marine1.attack()) == marine2, 즉 마린1이 마린2를 두번 공격
	

	/*
	두번 공격이 아닌, 전혀 엉뚱한 결과 발생
	리턴타입이 Marine이므로, 임시 객체 Marine을 생성해서* this의 내용으로 복사가 되고, 이 임시 객체에 대한 be_attacked()함수가 호출됨
	*/
	//marine2.be_attacked2(marine1.attack()).be_attacked2(marine1.attack()); 

	marine1.show_status();
	marine2.show_status();
}