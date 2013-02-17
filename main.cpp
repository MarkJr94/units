#include "Units.hpp"

#include <iostream>

using namespace std;

int main()
{
	typedef Value<Length,kilo> Kilometer;
	typedef Value<Length,mega,double> Megameter;
	typedef ComputeUnitDiv<Length,Time>::unit Velocity;
	typedef Value<Velocity,one> MS;

	auto sum = Kilometer(100) + Kilometer(22);

	MS velocity = Value<Length>(5) / Value<Time>(20);

	Meter fall (.5*9.8*200.4*200.4);
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

