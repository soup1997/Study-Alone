#include <iostream>

class stack {
private:
	int stack_size; // 스택 사이즈
	int stack_count; // 스택에 저장된 데이터의 갯수(TOP값)
	int* p_stack; // 스택으로 사용할 메모리 주소를 가리킬 포인터

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
	if (p_stack != NULL) delete[] p_stack;// 기존에 사용하던 메모리가 있으면 해당 메모리를 제거한다.
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
	if (stack_count == 0) { // 저장된 stack이 없으면
		std::cout << "stack is empty" << std::endl;
	}

	else {
		std::cout << "Popped!" << std::endl;
		p_stack[stack_count] = 0; // 연결을 끊고 stack count를 감소시킨다.
		stack_count--;
	}
}

void stack::show_stack() {
	if (stack_count == 0) {
		std::cout << "stack is empty" << std::endl;
	}

	else {
		std::cout << "Stack에 저장된 값은 다음과 같습니다." << std::endl;
		for (int i = 0; i < stack_count; i++) {
			std::cout << i << " : " << p_stack[i] << std::endl;
		}
	}
}

int main(void) {
	stack stack;
	int s_size = 0;
	int tmp = 0;
	int button = -1; // 아무 숫자로 초기화
	int value = 0;
	std::cout << "Stack 사이즈를 입력하세요 : ";

	// 입력된 stack 사이즈가 양수인지 체크
	while (s_size <= 0)
	{
		std::cin >> tmp;
		if (tmp <= 0)
		{
			std::cout << "stack_size를 양수로 입력하세요, 현재 입력된 값 ->" << s_size << std::endl << std::endl;
			std::cout << "Stack 사이즈를 입력하세요 : ";
		}
		else s_size = tmp;
	}

	// 스택 생성
	stack.create_stack(s_size);


	std::cout << std::endl;
	std::cout << "1. Stack Push" << std::endl;
	std::cout << "2. Stack Pop" << std::endl;
	std::cout << "3. Stack Print" << std::endl;
	std::cout << "0. Exit program" << std::endl;
	std::cout << std::endl << std::endl;

	while (button != 0)
	{
		std::cout << "버튼 선택 : ";
		std::cin >> button;
		std::cout << std::endl << std::endl;
		switch (button)
		{
		case 1: // 입력한 값 저장
			std::cout << "저장할 값은 ? : ";
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