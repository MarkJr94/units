#define FP_T double

#include "Units.hpp"

#include <iostream>

using namespace std;

int main()
{
	using namespace SI;
	
	typedef Value<Velocity> MpS;
	typedef Value<Acceleration> MpSS;

	auto sum = 100.0_m + 22.0_m;

	MpS velocity = 5.0_m / 20._s;

	Meter fall = velocity * 20.4_s + .5 * MpSS(-9.8) * 20.4_s * 20.4_s;
	
	Newton grav_force = 100.0_kg * MpSS(9.8);

	Watt elec_power = Ampere(15) * Volt(20);
	
	Joule heat_added = Value<SpecificHeat>(4.1813) * 10.0_kg * 5.0_K;

	cout << "Value of 100m + 22m = " << sum << endl;
	cout << "Value of 5m / 20s = " << velocity << endl;
	cout << "Fall distance of an object on earth after 20.4s in meters with initial velocity .25m/s = " << fall << endl;
	cout << "Gravitational force on 100kg mass = " << grav_force << "N" << endl;
	cout << "Electrical Power of circuit with 15A current and 20V potential = " << elec_power << "W" << endl;
	cout << "Energy needed to raise 10kg of water 5C (5K) using 4.1813 as specific heat = " << heat_added << "J" << endl;

	return 0;
}

