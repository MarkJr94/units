#include "Units.hpp"

#include <iostream>

using namespace std;

int main()
{
	typedef Value<Length,kilo> Kilometer;
	typedef Value<Length,mega> Megameter;
	typedef ComputeUnitDiv<Length,Time>::unit Velocity;
    typedef ComputeUnitDiv<Velocity,Time>::unit Acceleration;
	typedef Value<Velocity,one> MS;
    typedef Value<Acceleration, one> MpSS;

	auto sum = Kilometer(100) + Kilometer(22);

	MS velocity = Meter(5) / Second(20);

	Meter fall = Meter(MpSS(9.8) * Second(200.4) * Second(200.4))/2;
	Kilometer kilofall = fall.prefix_conv<kilo>();
	Megameter megafall = fall.prefix_conv<mega>();

	cout << "Value of 100km + 22km = " << sum << endl;
	cout << "Value of 5m / 20s = " << velocity << endl;
	cout << "Fall distance of an object on earth after 200.4s in meters = " << fall << endl;
	cout << "Fall distance of an object on earth after 200.4s in kilometers = " << kilofall << endl;
	cout << "Fall distance of an object on earth after 200.4s in megameters = " << megafall << endl;

	cout.flush();
	return 0;
}

