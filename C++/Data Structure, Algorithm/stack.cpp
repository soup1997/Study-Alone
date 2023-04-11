#include <iostream>

class stack {
private:
	int stack_size; // ���� ������
	int stack_count; // ���ÿ� ����� �������� ����(TOP��)
	int* p_stack; // �������� ����� �޸� �ּҸ� ����ų ������

public:
	stack();
	~stack();
	void create_stack(int size);
	void push(int value);
	void pop();
	void show_stack();
};

stack::stack() {
	stack_size = 0;
	stack_count = 0;
	p_stack = NULL;
}

stack::~stack() {
	if (p_stack != NULL) {
		delete[] p_stack;
	}
}

void stack::create_stack(int size) {
	if (p_stack != NULL) delete[] p_stack;// ������ ����ϴ� �޸𸮰� ������ �ش� �޸𸮸� �����Ѵ�.
	stack_size = size;
	p_stack = new int[stack_size];
}

void stack::push(int value) {
	if (stack_count < stack_size) {
		*(p_stack + stack_count) = value;
		stack_count++;
	}

	else {
		std::cout << "stack is full" << std::endl;
	}
}

void stack::pop() {
	if (stack_count == 0) { // ����� stack�� ������
		std::cout << "stack is empty" << std::endl;
	}

	else {
		std::cout << "Popped!" << std::endl;
		p_stack[stack_count] = 0; // ������ ���� stack count�� ���ҽ�Ų��.
		stack_count--;
	}
}

void stack::show_stack() {
	if (stack_count == 0) {
		std::cout << "stack is empty" << std::endl;
	}

	else {
		std::cout << "Stack�� ����� ���� ������ �����ϴ�." << std::endl;
		for (int i = 0; i < stack_count; i++) {
			std::cout << i << " : " << p_stack[i] << std::endl;
		}
	}
}

int main(void) {
	stack stack;
	int s_size = 0;
	int tmp = 0;
	int button = -1; // �ƹ� ���ڷ� �ʱ�ȭ
	int value = 0;
	std::cout << "Stack ����� �Է��ϼ��� : ";

	// �Էµ� stack ����� ������� üũ
	while (s_size <= 0)
	{
		std::cin >> tmp;
		if (tmp <= 0)
		{
			std::cout << "stack_size�� ����� �Է��ϼ���, ���� �Էµ� �� ->" << s_size << std::endl << std::endl;
			std::cout << "Stack ����� �Է��ϼ��� : ";
		}
		else s_size = tmp;
	}

	// ���� ����
	stack.create_stack(s_size);


	std::cout << std::endl;
	std::cout << "1. Stack Push" << std::endl;
	std::cout << "2. Stack Pop" << std::endl;
	std::cout << "3. Stack Print" << std::endl;
	std::cout << "0. Exit program" << std::endl;
	std::cout << std::endl << std::endl;

	while (button != 0)
	{
		std::cout << "��ư ���� : ";
		std::cin >> button;
		std::cout << std::endl << std::endl;
		switch (button)
		{
		case 1: // �Է��� �� ����
			std::cout << "������ ���� ? : ";
			std::cin >> value;
			stack.push(value);
			break;

		case 2:
			stack.pop();
			break;

		case 3:
			stack.show_stack();
			break;
		}
	}
	return 0;
}