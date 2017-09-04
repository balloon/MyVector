#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "MyVector.h"

using namespace std;
//template<typename Ty>
//class reverse_pointer {
//	typedef Ty value;
//	
//private:
//	value p;
//public:
//	reverse_pointer() :p(nullptr) {}
//	reverse_pointer(value s) :p(s) {}
//	reverse_pointer(const reverse_pointer<Ty> &t) :p(t.p) {}
//	reverse_pointer<Ty>& operator=(const reverse_pointer<Ty> t) {
//		p = t.p;
//	}
//	reverse_pointer<Ty>& operator=(const value t) {
//		p = t;
//	}
//	value& operator++() {
//		--p;
//		return p;
//	}
//	value operator++(int) {
//		auto t = p;
//		--p;
//		return t;
//	}
//	value& operator--() {
//		++p;
//		return p;
//	}
//	value operator--(int) {
//		auto t = p;
//		++p;
//		return t;
//	}
//	auto operator*()->decltype(*p) {
//		return *p;
//	}
//	friend bool operator==(const reverse_pointer<Ty>,const reverse_pointer<Ty>);
//	friend bool operator!=(const reverse_pointer<Ty>, const reverse_pointer<Ty>);
//	friend bool operator<(const reverse_pointer<Ty>, const reverse_pointer<Ty>);
//	friend bool operator>(const reverse_pointer<Ty>, const reverse_pointer<Ty>);
//};
//template<typename Ty>
//bool operator==(const reverse_pointer<Ty> foo, const reverse_pointer<Ty> bat) {
//	if (foo.p == bat.p)
//		return true;
//	else
//		return false;
//}
//template<typename Ty>
//bool operator!=(const reverse_pointer<Ty> foo, const reverse_pointer<Ty> bat) {
//	if (foo == bat)
//		return false;
//	else
//		return true;
//}
//template<typename Ty>
//bool operator<(const reverse_pointer<Ty> foo, const reverse_pointer<Ty> bat) {
//	if (foo.p < bat.p)
//		return true;
//	else
//		return false;
//}
//template<typename Ty>
//bool operator>(const reverse_pointer<Ty> foo, const reverse_pointer<Ty> bat) {
//	if (foo < bat || foo == bat)
//		return false;
//	else
//		return true;
//};
class A {
public: A(string t,string t2):a(t),b(t2) {}
		A(const A& t) :a(t.a), b(t.b) {}
		A() :a(""), b("") {}
		A& operator=(const A &t) {
			a = t.a;
			b = t.b;
			return *this;
		}
		void print() {
			cout << a << b << endl;
		}
	friend	ostream& operator<<(ostream &os ,const A &t) {
		os<< t.a <<t.b;
		return os;
		}
	~A() {}
private: string a;
		 string b;
};
int checkCPU(void)
{   union
		    {
		        int a;
		        char b;
		   }c;
	   c.a = 1;
   return (c.b == 1);
	}

int main()
{
	MyVector<A> x(10);
	
}