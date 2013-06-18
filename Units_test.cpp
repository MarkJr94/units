#define FP_T double

#include "Units.hpp"

#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    using namespace SI;
    
	typedef UnitDiv<Length,Time>::unit Velocity;
    typedef UnitDiv<Velocity,Time>::unit Acceleration;
    typedef UnitMul<Mass, Acceleration>::unit Force;
	
	typedef Value<Velocity> MpS;
    typedef Value<Acceleration> MpSS;
    typedef Value<Force> Newton;

	auto sum = 100.0m + 22.0m;

	MpS velocity = 5.m / 20.s;

	Meter fall = velocity * 20.4s + .5 * MpSS(9.8) * 20.4s * 20.4s;
	
	Newton grav_force = 100.kg * MpSS(9.8);

	cout << "Value of 100m + 22m = " << sum << endl;
	cout << "Value of 5m / 20s = " << velocity << endl;
	cout << "Fall distance of an object on earth after 20.4s in meters with initial velocity .25m/s = " << fall << endl;
	cout << "Underlying type of Value<Unit> is " << typeid(sum.val()).name() << endl;
	cout << "Gravitational force on 100kg mass = " << grav_force << "N" << endl;

	cout.flush();
	return 0;
}

