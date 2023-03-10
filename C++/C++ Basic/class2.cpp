#include <iostream>
#include <cstring>

#pragma warning(disable: 4996)

class Marine {
	// ���������� �������� ������� �⺻������ private��
	int hp;
	int coord_x, coord_y;
	int damage;
	char* name;
	bool is_dead;

public:
	Marine(); // default ������, �����ڴ� �����ε� ����
	Marine(int x, int y, const char* marine_name); // ���� ������, �̸����� ����
	Marine(int x, int y); // ���� ������, x, y ��ǥ�� ���� ����

	~Marine(); // �Ҹ���, ���ڸ� ������ ����, �����ε� �Ұ���

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y, const char* marine_name) {
	// �迭�� �����Ҵ�
	// int *arr = new int[arr_size];
	// char�ڷ������ٰ� ũ����� �����Ͽ� �����Ҵ�(�迭 ���� �Ҵ�� ����)
	// �����Ҵ� �� �������� ������ ��� �޸� �����Ͽ�, �޸� ���� ���� �߻�
	// ���� �����Ҵ�� ���ڿ��� �Ҹ��ڿ� �־, ��ü�� �Ҹ�ɶ� �ڵ����� ���������ϵ��� ��������
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);

	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::~Marine() {
	std::cout << name << "�� �Ҹ��� ȣ��" << std::endl;
	if (name != NULL) {
		delete[] name;
	}
}
void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}


int Marine::attack() {
	return damage;
}

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}

void Marine::show_status() {
	std::cout << "*** Marine *** " << std::endl;
	std::cout << "Location: ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP: " << hp << std::endl;
}

class Photon_Cannon {
private:
	int hp, shiled;
	int coord_x, coord_y;
	int damage;
	char* name;

public:
	Photon_Cannon(int x, int y, const char* cannon_name);
	Photon_Cannon(const Photon_Cannon& pc);
	~Photon_Cannon();
	void show_status();
};

Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
	std::cout << "���� ������ ȣ��!" << std::endl;
	hp = pc.hp;
	shiled = pc.shiled;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;

	name = new char[strlen(pc.name) + 1];
	strcpy(name, pc.name);
}

Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
	std::cout << "������ ȣ��!" << std::endl;
	hp = shiled = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = new char[strlen(cannon_name) + 1];
	strcpy(name, cannon_name);
}

Photon_Cannon::~Photon_Cannon() {
	if (name)
	{
		delete[] name;
	}
}


void Photon_Cannon::show_status() {
	std::cout << "Photton Cannon" << name << std::endl;
	std::cout << "Location: ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}


int main()
{
	Marine* marines[100];

	marines[0] = new Marine(2, 3, "Marine 2");
	marines[1] = new Marine(3, 5, "Marine 1");

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "���� 1�� ���� 2�� ����!" << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();
	
	std::cout << std::endl;

	Photon_Cannon pc1(3, 3, "Cannon");
	Photon_Cannon pc2(pc1);
	Photon_Cannon pc3 = pc2;


	pc1.show_status();
	pc2.show_status();

	delete marines[0];
	delete marines[1];
}


/*
Console Result


*** Marine ***
Location: ( 2 , 3 )
 HP: 50
*** Marine ***
Location: ( 3 , 5 )
 HP: 50

���� 1�� ���� 2�� ����!
*** Marine ***
Location: ( 2 , 3 )
 HP: 45
*** Marine ***
Location: ( 3 , 5 )
 HP: 50

������ ȣ��!
���� ������ ȣ��!
���� ������ ȣ��!
Photton CannonCannon
Location: ( 3 , 3 )
 HP : 100
Photton CannonCannon
Location: ( 3 , 3 )
 HP : 100
Marine 2�� �Ҹ��� ȣ��
Marine 1�� �Ҹ��� ȣ��


*/