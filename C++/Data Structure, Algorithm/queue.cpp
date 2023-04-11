#include <iostream>
#define QUEUESIZE 20

class Queue {
private:
	int front;
	int rear;
	int size;
	int* p_queue;

public:
	Queue();
	~Queue();
	void push(int value);
	void pop();
	bool empty();
	bool is_full();
	void show_queue();
};

Queue::Queue() : front(0), rear(0), size(QUEUESIZE), p_queue(NULL) {
	if (p_queue != NULL) delete[] p_queue;
	p_queue = new int[size];
}

Queue::~Queue() {
	delete[] p_queue;
}

void Queue::push(int value) {
	if (!is_full()) {
		p_queue[rear] = value;
		rear = (rear + 1) % size;
	}

	else std::cout << "Queue is Full" << std::endl;
}

void Queue::pop() {
	if (!empty()) front = (front + 1) % size;

	else std::cout << "Queue is empty" << std::endl;
}

bool Queue::empty() {
	if (rear == front) return true;
	
	else return false;
}

bool Queue::is_full() {
	if ((rear + 1) % size == front) return true;

	else return false;
}

void Queue::show_queue() {
	for (int i = front; i < rear; i++) 
	{
		std::cout << i << " : " << p_queue[i] << std::endl;
	}
}

int main() {
	Queue q;
	int button = -1;
	int value = 0;

	while (button != 0)
	{
		std::cout << "1: Push " << "2: Pop " << "3: Show " << std::endl;

		std::cout << "버튼 선택 : ";
		std::cin >> button;
		std::cout << std::endl << std::endl;

		switch (button)
		{
		case 1: // 입력한 값 저장
			std::cout << "저장할 값은 ? : ";
			std::cin >> value;
			q.push(value);
			break;

		case 2:
			q.pop();
			break;

		case 3:
			q.show_queue();
			break;
		}
	}
		return 0;
}