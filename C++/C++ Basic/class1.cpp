#include <iostream>

// C++에서 하나의 클래스에서 생성된 인스턴스는 각각 독립된 메모리 공간에 저장된 자신만의 멤버 변수를 가지지만, 멤버 메서드는 모든 인스턴스가 공유한다.

class Date {
	int year_;
	int month_;
	int day_;

private: // 접근지정자 private == 해당 클래스 내부 멤버 메서드에서만 사용 가능, 외부 접근 불가능
	int test_variable = 0;

public: // 접근지정자 public == 외부에서 접근 가능
	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	void ShowDate();

	int GetCurrentMonthTotalDays(int year, int month) { // 클래스 내부에서 함수 정의
		static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month != 2)
		{
			return month_day[month - 1];
		}
		else if (year % 4 == 0 && year % 100 != 0)
		{
			return 29;
		}

		else return 28;
	}

	Date(int year, int month, int day) // 생성자 Constructor
	{
		year_ = year;
		month_ = month;
		day_ = day;
	}
};

void Date::SetDate(int year, int month , int day) // 클래스 외부에서 함수 정의
{
	year_ = year;
	month_ = month;
	day_ = day;
}

void Date::AddDay(int inc) {
	while (true)
	{
		int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

		if (day_ = inc <= current_month_total_days)
		{
			day_ += inc;
			return;
		}

		else
		{
			inc -= (current_month_total_days - day_ + 1);
			day_ = 1;
			AddMonth(1);
		}
	}
}

void Date::AddMonth(int inc) {
	AddYear((inc + month_ - 1) / 12);
	month_ += inc % 12;
	month_ = (month_ == 12 ? 12 : month_ % 12);
}

void Date::AddYear(int inc) {
	year_ += inc;
}

void Date::ShowDate() {
	std::cout << "오늘은" << year_ << " 년" << month_ << " 월" << day_ << "일 입니다." << std::endl;
}


int main() {
	Date day(2011, 3, 1);
	day.ShowDate();

	day.SetDate(2012, 8, 4);
	day.AddDay(2500);
	day.ShowDate();

	return 0;
}