#include <iostream>
#include <string>
#pragma warning(disable:4996)

//====================== 클래스 상속 튜토리얼 ==========================
class Base {
protected:
	std::string parent_string;

public:
	Base() : parent_string("기반") {
		std::cout << "기반 클래스" << std::endl;
	}

	void what() {
		std::cout << parent_string << std::endl;
	}
};

class Derived : public Base {

private:
	std::string child_string;

public:
	Derived() : Base(), child_string("파생") {
		std::cout << "파생 클래스" << std::endl;

		Base::what();
		Derived::what();

		Base::parent_string = "바꾸기"; // protected keyword에 선언된 변수나 메서드는 상속받아 사용가능하다.
	}

	void what() {
		std::cout << child_string << std::endl;
	}
};
//=======================================================================

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

	void print_info() {
		std::cout << name << " (" << position << " , " << age << ") ==>" << calculate_pay() << "만원" << std::endl;
	}

	int calculate_pay() {
		return 200 + rank * 50;
	}
};

class Manager : public Employee {
private:
	int year_of_service;

public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service): Employee(name, age, position, rank), year_of_service(year_of_service) {}

	Manager(const Manager& manager): Employee(manager.name, manager.age, manager.position, manager.rank) {
		year_of_service = manager.year_of_service;
	}

	Manager() : Employee() {}

	int calculate_pay() {
		return 200 + rank * 50 + 5 * year_of_service;
	}

	void print_info() {
		std::cout << name << " (" << position << " , " << age << " , "
			<< year_of_service << "년차) ==> " << calculate_pay() << "만원" << std::endl;
	}
};

class EmployeeList {
private:
	int alloc_employee;

	int current_employee;
	int current_manager;

	Employee** employee_list;
	Manager** manager_list;

public:
	EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
		employee_list = new Employee * [alloc_employee];
		manager_list = new Manager * [alloc_employee];

		current_employee = 0;
		current_manager = 0;
	}

	void add_employee(Employee* employee) {
		employee_list[current_employee] = employee;
		current_employee++;
	}

	void add_manager(Manager* manager) {
		manager_list[current_manager] = manager;
		current_manager++;
	}

	int current_employee_num() {
		return current_employee + current_manager;
	}

	void print_employee_info() {
		int total_pay = 0;

		for (int i = 0; i < current_employee; i++) {
			employee_list[i]->print_info();
			total_pay += employee_list[i]->calculate_pay();
		}

		for (int i = 0; i < current_manager; i++) {
			manager_list[i]->print_info();
			total_pay += manager_list[i]->calculate_pay();
		}
		std::cout << "총 비용: " << total_pay << "만원" << std::endl;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; i++) {
			delete employee_list[i];
		}

		for (int i = 0; i < current_manager; i++) {
			delete manager_list[i];
		}

		delete[] employee_list;
		delete[] manager_list;
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
