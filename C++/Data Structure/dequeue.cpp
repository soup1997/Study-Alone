// 양쪽끝에서 삽입과 삭제가 가능, Double Ended Queue
#include <iostream>

class Dequeue {
private:
	int head;
	int tail;
	int init_index;
	int* dat;

public:
	Dequeue(int size): head(size), tail(size), init_index(size) {
		dat = new int[(2*size) + 1];
	}

	void push_front(int x) {
		dat[--head] = x;

		if (head > init_index) {
			head = init_index;
		}
	}

	void push_back(int x) {
		dat[tail++] = x;

		if (tail < init_index) {
			tail = init_index;
		}
	}

	void pop_front() {
		if (tail == head) {
			std::cout << "Dequeu is empty" << std::endl;
			return;
		}

		else head++;
	}

	void pop_back() {
		if (tail == head)
		{
			std::cout << "Dequeu is empty" << std::endl;
			return;
		}
		else tail--;
	}

	void print_dequeue() {
		if (head == tail) {
			std::cout << "Dequeu is empty" << std::endl;
			return;
		}
		else {
			for (int i = head; i < tail; i++) {
				std::cout << dat[i] << " -> ";
			}
			std::cout << std::endl;
		}
	}
	int print_front() {
		return dat[head];
	}

	int print_back() {
		return dat[tail - 1];
	}

	~Dequeue() {
		delete[] dat;
	}
};

int main() {
	const int MX = 1000;
	Dequeue dequeue(MX);
	
	dequeue.push_front(10);
	dequeue.push_back(50);
	dequeue.push_front(24);
	dequeue.print_dequeue(); // 24 -> 10 -> 50 ->

	dequeue.pop_front();
	dequeue.pop_back();
	dequeue.push_back(58);
	dequeue.print_dequeue(); // 10 -> 58 ->

	dequeue.pop_front();
	dequeue.pop_back();
	dequeue.print_dequeue(); // Dequeu is empty 

	return 0;
}