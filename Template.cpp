/*
ѧϰC++ģ��
������ת�Ľ̳̣�д�úܺ���⣬��ûд�꣺https://github.com/wuye9036/CppTemplateTutorial

*/

#include<iostream>
#include<bitset>
#include<vector>
using namespace std;

#define WRONG_CODE_ENABLED 0

// ---------------
// �ɱ�������ģ�����
// ---------------

// print���������������ͣ����FG_TRACE

// �ػ�
void print() {}

template<class T, class... Ts>
void print(const T& args1st, const Ts&... args)
{
	cout << args1st << endl;
	cout << (sizeof...(args)) << " params left:" << endl;
	print(args...);
}

// ����
template<class... Ts>
void print(const Ts&... args)
{
	cout << "!" << endl;
}

void test_print()
{
	print(1, 2, "helo", bitset<16>(0101), 42, 9.30f);
}


// ------------------Tuple------------------
// .	 .	  .	   .	.	 Head
// .	 .	  .	   .	Head  
// .	 .	  .	   Head	  
// .	 .	  Head	
// .	 Head
// Head

// �����������͵�������Ӧ�ó����������ܣ�

template<class... Ts> class Tuple;

template<> class Tuple<> {};

template<class Head, class... Ts>
class Tuple<Head, Ts...> : private Tuple<Ts...>
{
	typedef Tuple<Ts...> inherited;
public:
	Tuple() {}
	Tuple(const Head& h, const Ts&... ts)
		: head_(h), inherited(ts...) {}

	const Head& head() const { return head_; }
	const inherited& tail() const { return *this; }

	/*
	��ô�����ڲ�get��auto�Ƶ�
	template<size_t I>
	const auto& get() const { return tail().get<I - 1>;	}

	template<0>
	const auto& get() const { return head(); }
	*/

	template<size_t I>
	const auto& get() const;

protected:
	Head head_;
};

template<size_t N, typename Head> class TupleElem;

template<size_t N, typename Head, typename... Ts>
class TupleElem<N, Tuple<Head, Ts...>> : public TupleElem <N - 1, Tuple<Ts...>>
{
public:
	typedef typename TupleElem<N, Tuple<Head, Ts...>>::Type type;
	static const type& Get(const Tuple<Head, Ts...>& tuple)
	{
		return TupleElem<N - 1, Tuple<Ts...>>::Get(tuple.tail());
	}
};

template<typename Head, typename... Ts>
class TupleElem<0, Tuple<Head, Ts...>>
{
public:
	typedef Head Type;
	static const Type& Get(const Tuple<Head, Ts...>& tuple)
	{
		return tuple.head();
	}
};

template<size_t I, typename Head, typename... Ts>
typename const TupleElem<I, Tuple<Head, Ts...>>::Type& Get(const Tuple<Head, Ts...>& t)
{
	return TupleElem<I, Tuple<Head, Ts...>>::Get(t);
}

template<class Head, class... Ts>
template<size_t I>
const auto& Tuple<Head, Ts...>::get() const
{
	return Get<I>(*this);
}

// -------------- std tuple --------------

#include <tuple>

void test_tuple()
{
	Tuple<int, float, string> t1(1, 0.1f, "h1");
	tuple<int, float, string> t2(2, 0.2f, "h2");

	bool b = is_same<decltype(t1), decltype(t2)>();

	cout << Get<0>(t1) << endl;
	cout << Get<1>(t1) << endl;
	cout << Get<2>(t1) << endl;

	cout << t1.get<0>() << endl;
	cout << t1.get<1>() << endl;
	cout << t1.get<2>() << endl;

	print(t1.get<0>(), t1.get<1>(), t1.get<2>());

	cout << get<0>(t2) << endl;
	cout << get<1>(t2) << endl;
	cout << get<2>(t2) << endl;
}

// SFINAE

template <int I> struct X { };
template <template <class T> class> struct Z { };
template <class T> void f(typename T::Y*) {}
template <class T> void g(X<T::N>*) {}
template <class T> void h(Z<T::template TT>*) {}
struct A {};
struct B { int Y; };
struct C { typedef int N; };
struct D { typedef int TT; };
struct B1 { typedef int Y; };
struct C1 { static const int N = 0; };
struct D1 {
	template <typename T>
	struct TT
	{
	};
};

void test_sfinae() {

#if WRONG_CODE_ENABLED
	// ���и�������Ƶ�ʧ�ܣ�
	f<A>(0); // ������Ա Y
	f<B>(0); // B �� Y ��Ա��������
	g<C>(0); // C �� N ��Ա���Ƿ�����
	h<D>(0); // D �� TT ��Ա����ģ��
#endif

	// ���и�������Ƶ��ɹ���
	f<B1>(0);
	g<C1>(0);
	h<D1>(0);
}