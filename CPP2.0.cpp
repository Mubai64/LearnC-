/* 
ѧϰC++2.0������
�ο�:

��ݡ���C++11������:
��Ƶ��https://www.bilibili.com/video/av51863195?from=search&seid=3610634846288253061
���C++�γ�PPT�����룺https://github.com/harvestlamb/Cpp_houjie
���ƽ̳̣�https://light-city.club/sc/c%2B%2B2.0/c%2B%2B11/c%2B%2B11/

C++ѧϰ��վ��

C++�ֲᣬ�����ģ�������Ӣ���ռ�����⣺
https://zh.cppreference.com/w/cpp/11

C++�����˲��ͣ�
http://www.stroustrup.com/C++.html

��һ����������վ���о������һ�����ã�
http://www.cplusplus.com/

�кõ�ѧϰ�����벹��
*/

#include<iostream>
#include<vector>
using namespace std;

namespace Cpp2
{

// C++11 ������

// initializer list
namespace _1 {

	struct Foo {
		Foo() {}
		Foo(int a, int b) {}
	};

	Foo f1(1, 2);
	Foo f2 = Foo(1, 2);
	Foo f3{ 1, 2 };  // C++11

}


// nullptr
// C++11֮ǰNULL�޷�ƥ��ָ������
namespace _2 {

	void f(int) { cout << "int" << endl; }
	void f(void*) { cout << "ptr" << endl; }

	void test_nullptr()
	{

		f(0);
		f(NULL);
		f(nullptr);

		cout << typeid(nullptr).name() << endl;
		nullptr_t a;
		cout << typeid(nullptr_t).name() << endl;

		system("pause");
	}

}

// alias
// using xxx = int; 
// typedef int xxx;
namespace _3 {

	template<typename T>
	struct myalloc : std::allocator<T> {
	};

	template<typename T>
	using Vec = std::vector<T, myalloc<T>>;

	Vec<int> vi;

}

// lambda
// [ captures ] <tparams>(optional)(c++20) ( params ) specifiers exception attr -> ret requires(optional)(c++20) { body }
namespace _4 {

	void test_lambda()
	{
		int id = 0;
		auto f = [id]() mutable -> int { std::cout << id; return ++id; };

		decltype(f) f1(); // lambda��һ��functor

		std::cout << typeid(f).name() << std::endl;

		id = 42;
		// std::cout << f1()() << std::endl; 
		std::cout << f() << std::endl;
		std::cout << f() << std::endl;
		std::cout << id << std::endl;
	}

}

}

int main()
{
	return 0;
}

