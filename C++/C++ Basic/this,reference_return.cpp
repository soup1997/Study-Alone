// �ڽ��� ����Ű�� ������ this
#include <iostream>

class Marine {
private:
	static int total_marine_num; // ��� �ν��Ͻ��� �����ϴ� �ϳ��� static ����
	const static int i = 0; // const������ ������ ���ÿ� �ʱ�ȭ ����

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	int attack() const; // ��� ��� �Լ�, �ٸ� ������ ���� �ٲ��� �ʴ� �Լ���� ����ϴ� ��
	
	Marine& be_attacked(int damage_earn); // ��ü�� reference�� return
	Marine be_attacked2(int damage_earn); // reference�� return�ϴ� �Ͱ� �񱳸� ���� �ӽ� �Լ�

	void move(int x, int y);

	void show_status();
	static void show_total_marine(); // ��� �ν��Ͻ��� �����ϴ� �ϳ��� static �Լ�

	~Marine();
};

// Static variable, method, initialization
int Marine::total_marine_num = 0;

void Marine::show_total_marine() {
	std::cout << "��ü ���� ��: " << total_marine_num << std::endl;
}

/* 
Initializer list
�ν��Ͻ� ������ �ʱ�ȭ�� ���ÿ� ����
reference ������, const ������ ������ ���ÿ� �ʱ�ȭ�� ����Ǿ�� ��
���� �ʱ�ȭ ����Ʈ�� �ش� �����鿡 ���� Ưȭ�� ����̶� �� �� �ִ�.
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
	std::cout << " ���� �� ���� ��: " << total_marine_num << std::endl;
}

int main() {
	Marine marine1(2, 3, 5);
	marine1.show_status();

	Marine marine2(3, 5, 10);
	marine2.show_status();

	std::cout << std::endl << "���� 1�� ���� 2�� ���� !" << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack()); // (marine2.be_attacked(marine1.attack()) == marine2, �� ����1�� ����2�� �ι� ����
	

	/*
	�ι� ������ �ƴ�, ���� ������ ��� �߻�
	����Ÿ���� Marine�̹Ƿ�, �ӽ� ��ü Marine�� �����ؼ�* this�� �������� ���簡 �ǰ�, �� �ӽ� ��ü�� ���� be_attacked()�Լ��� ȣ���
	*/
	//marine2.be_attacked2(marine1.attack()).be_attacked2(marine1.attack()); 

	marine1.show_status();
	marine2.show_status();
}