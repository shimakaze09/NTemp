//
// Created by Admin on 3/12/2024.
//

#include <array>
#include <iostream>
#include <type_traits>
#include <string>

#include "MyTemplate/SI.hxx"

using namespace std;
using namespace My;

template<typename Base>
struct IPeople : Base {
	using Base::Base;

	IPeople(const string & name) :name(name) {}
	string name;
};

template<typename Base>
struct ISing : Base {
	using Base::Base;

	void Sing() {
		cout << "Sing";
	}
};

template<typename Base>
struct IJump : Base {
	using Base::Base;

	void Jump() {
		cout << "Jump";
	}
};

template<typename Base>
struct IRap : Base {
	using Base::Base;

	void Rap() {
		cout << "Rap";
	}
};

template<typename Base>
struct IBasketball : Base {
	using Base::Base;

	void Basketball() {
		cout << "Basketball";
	}
};

struct CXK : SII<IBasketball, ISing, IJump, IRap, IPeople>::Ttype<> {
	CXK() : Ttype("CXK") {}
};

int main() {
	CXK cxk;
	cout << "Hello, everyone. I am a trainee with two and a half years of practice, " << cxk.name << endl
		<< "I like ";
	cxk.Sing();
	cout << ", ";
	cxk.Jump();
	cout << ", ";
	cxk.Rap();
	cout << ", ";
	cxk.Basketball();
	cout << "!";

	return 0;
}