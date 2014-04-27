/*This code sample is absolutly not mine, all credit goes to "nsf" who posted this in the comments section
of "The Way of the Exploding Tuple" video on "Going Native 2013" website.
I suppose this is some public domain stuff :p

Comment link : http://channel9.msdn.com/Events/GoingNative/2013/The-Way-of-the-Exploding-Tuple#c635168374212652019
Sample code link : http://ideone.com/abiKOo
*/

#include <cstdio>
#include <tuple>
#include <utility>
#include <type_traits>

template<int ...I> struct index_tuple_type {
	template<int N> using append = index_tuple_type<I..., N>;
};
template<int N> struct make_index_impl {
	using type = typename make_index_impl<N-1>::type::template append<N-1>;
};
template<> struct make_index_impl<0> { using type = index_tuple_type<>; };
template<int N> using index_tuple = typename make_index_impl<N>::type;

template <typename I, typename ...Args>
struct func_traits;

template <typename R, int ...I, typename ...Args>
struct func_traits<R, index_tuple_type<I...>, Args...> {
	template <typename TT, typename FT>
	static inline R call(TT &&t, FT &&f) {
		return f(std::get<I>(std::forward<TT>(t))...);
	}
};

#define _explode_variant(_T)										\
template <typename FT, typename ...Args, typename R = typename std::result_of<FT(Args&&...)>::type>	\
inline R explode(_T t, FT &&f) {									\
	return func_traits<R, index_tuple<sizeof...(Args)>, Args...>					\
		::call(std::forward<_T>(t), std::forward<FT>(f));					\
}

_explode_variant(const std::tuple<Args...>&)
_explode_variant(      std::tuple<Args...>&)
_explode_variant(      std::tuple<Args...>&&)

#undef _explode_variant

//----------------------------------------------------------------------

void test1(int i, char c) {
	printf("%d %c\n", i, c);
}

struct S {
	int operator()(int, int) { return 5; }
	double operator()(int) { return 3.14; }
};

struct Object {
	Object() = default;
	Object(const Object&)  { printf("copying\n"); }
	Object(Object&&) { printf("moving\n"); }
};

void test5(Object a, Object b, Object c) {
	printf("in test5, moving\n");
}

void test6(Object a, Object b, Object c) {
	printf("in test6, copying\n");
}

int main() {
	std::tuple<int, char> t1{57, 'a'};
	explode(t1, test1);

	S s;
	// test correct return value deduction, based on implicit type conversion
	std::tuple<float> t2{5};
	printf("%f\n", explode(t2, s));

	std::tuple<int, int> t3{1, 7};
	printf("%d\n", explode(t3, s));

	// lambdas
	auto t4 = std::make_tuple("value: ", 10);
	explode(std::move(t4), [](const char *prompt, int value) { printf("%s%d\n", prompt, value); });

	// move!
	printf("starting test 5\n");
	auto t5 = std::make_tuple(Object{}, Object{}, Object{});
	printf("exploding, moving!\n");
	explode(std::move(t5), test5);

	// copy
	printf("starting test 6\n");
	auto t6 = std::make_tuple(Object{}, Object{}, Object{});
	printf("exploding, copying!\n");
	explode(t6, test6);
}


