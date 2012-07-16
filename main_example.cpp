//============================================================================
// Name        : main.cpp
// Author      : Soki Sakurai
// Version     :
// Copyright   : free for all
// Description : UnitAndValue sample program
//============================================================================

#include "Value.hpp"
#include "ValueMath.hpp"
#include "Rational.hpp"

#include <iostream>

using namespace std;
using namespace hongo;

int main() {
	//A minimum kinetic energy of De Lorean when traveling through time.
	Value mass(1244,"kg");
	Value speed(88,"mi/h");
	Value Ek = 0.5*mass*speed*speed;
	cout << Ek.getValueIn("kJ") << " kJ" << endl;

	//An initial speed when Doraemon jumps at the sight of a mouse.
	Value g(9.8,"m/s^2");
	Value h(129.3,"cm");
	Rational index(1,2);	//index=1/2
	Value v = ValueMath::vpow(2*g*h, index);
//	Value v = ValueMath::vsqrt(2*g*h);		//equivalent expression
	cout << v.getValueIn("m/s") << " m/s" << endl;

	return 0;
}
