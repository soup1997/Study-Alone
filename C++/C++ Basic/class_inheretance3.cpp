#include <iostream>
#include <string>
#pragma warning(disable:4996)


// virtual, overide

class Employee {
	// Manager 클래스에서 상속받아 접근해야 하므로 private 키워드로 지정하면 접근이 불가능
protected:
	std::string name;
	int age;

	std::string position;
	int rank;

public:
	Employee(std::string name, int age, std::string position, int rank) : name(name), age(age), position(position), rank(rank) {}

	Employee(const Employee& employee) {
		name = employee.name;
		age = employee.age;
		position = employee.position;
		rank = employee.rank;
	}

	Employee() {}

	// vitual: 가상 함수, 해당 클래스를 상속받는 하위 클래스에서 virtual 키워드의 함수를 재정의(오버라이딩)한다는 뜻
	virtual void print_info() {
		std::cout << name << " (" << position << " , " << age << ") ==>" << calculate_pay() << "만원" << std::endl;
	}

	virtual int calculate_pay() {
		return 200 + rank * 50;
	}
};

class Manager : public Employee {
private:
	int year_of_service;

public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service) : Employee(name, age, position, rank), year_of_service(year_of_service) {}

	// override: virtual과 똑같은 기능, 다만 키워드를 붙이는 위치가 다름(함수 이름 뒤에), 이 가상함수가 상속받아서 오버라이딩한 함수라는 것을 의미함
	int calculate_pay() override{
		return 200 + rank * 50 + 5 * year_of_service;
	}

	void print_info() override{
		std::cout << name << " (" << position << " , " << age << " , "
			<< year_of_service << "년차) ==> " << calculate_pay() << "만원" << std::endl;
	}
};

class EmployeeList {
private:
	int alloc_employee;
	int current_employee;

	Employee** employee_list;

public:
	EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
		employee_list = new Employee * [alloc_employee];
		current_employee = 0;
	}

	void add_employee(Employee* employee) {
		employee_list[current_employee] = employee;
		current_employee++;
	}

	int current_employee_num() {
		return current_employee;
	}

	void print_employee_info() {
		int total_pay = 0;

		for (int i = 0; i < current_employee; i++) {
			employee_list[i]->print_info();
			total_pay += employee_list[i]->calculate_pay();
		}

		std::cout << "총 비용: " << total_pay << "만원" << std::endl;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; i++) {
			delete employee_list[i];
		}

		delete[] employee_list;
	}
};
int main() {
	EmployeeList emp_list(10);

	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.add_employee(new Employee("하동훈", 34, "평사원", 1));
	emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
	emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
	emp_list.add_employee(new Employee("길성준", 36, "인턴", -1));

	emp_list.print_employee_info();

	return 0;
}