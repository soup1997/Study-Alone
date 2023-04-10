#include <iostream>

template <int N>
struct INT {
	static const int num = N;
};

template<typename a, typename b>
struct add {
	typedef INT<a::num + b::num> result;
};

template <typename a, typename b>
struct divide {
	typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div {
	// result 중에서 한개라도 true면 전체가 true
	static const bool result = (N::num % d::num == 0) || 
		check_div < N, typename add<d, one>::result>::result;
};

template <typename N>
struct _is_prime {
	static const bool result = !check_div<N, two>::result;
};

template<>
struct _is_prime<two> {
	static const bool result = true;
};

template<>
struct _is_prime<three> {
	static const bool result = true;
};

// 컴파일러는 어떤 식별자를 보았을때 기본으로 '값'이라고 가정한다.
// 따라서 어떤 식별자가 type이라면 typename이라는 키워드를 명시적으로 붙여 알려줘야한다.
template<typename N>
struct check_div <N, typename divide<N, two>::result> {
	static const bool result = N::num % (N::num / 2) == 0;
};

template<int N>
struct is_prime {
	static const bool result = _is_prime<INT<N>>::result;
};

int main() {
	std::cout << std::boolalpha;

	std::cout << "Is 2 prime ? ::" << is_prime<2>::result << std::endl;
	std::cout << "Is 10 prime ? ::" << is_prime<10>::result << std::endl;
	std::cout << "Is 11 prime ? ::" << is_prime<11>::result << std::endl;
	std::cout << "Is 61 prime ? ::" << is_prime<61>::result << std::endl;
}