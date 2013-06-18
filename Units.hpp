// Filename: Units.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef UNITS_HPP
#define UNITS_HPP

#include <cmath>
#include <cstdint>
#include <iostream>

#ifndef FP_T
#define FP_T double
#endif

namespace SI {

template <int length, int mass, int time, int current, int temp, int amount, int lum>
struct Unit {
	enum { m =length, kg = mass, s = time, A = current, K = temp, mol = amount, cd = lum};
};

template <class u1, class u2>
struct UnitMul {
	typedef Unit<u1::m + u2::m,u1::kg+u2::kg,u1::s+u2::s,u1::A+u2::A,u1::K+u2::K,u1::mol+u2::mol,u1::cd+u2::cd> unit;
};

template <class u1, class u2>
struct UnitDiv {
	typedef Unit<u1::m - u2::m,u1::kg-u2::kg,u1::s-u2::s,u1::A-u2::A,u1::K-u2::K,u1::mol-u2::mol,u1::cd-u2::cd> unit;
};

template <class Unit>
struct Value {
	constexpr explicit Value(FP_T val):
		_val(val) {}


	FP_T val() const { return _val; }

	Value& operator+=(const Value& rhs)
	{
		_val += rhs._val;
		return *this;
	}

	Value& operator-=(const Value& rhs)
	{
		_val -= rhs._val;
		return *this;
	}

	friend Value operator+(Value lhs, const Value& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend Value operator-(Value lhs, const Value& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend std::ostream& operator<<(std::ostream& os, const Value& val)
	{
		os << val._val;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Value& val)
	{
		is >> val._val;
		return is;
	}

    
    friend Value& operator*=(Value& lhs, const FP_T rhs)
    {
        lhs._val *= rhs;
        return lhs;
    }

    friend Value operator*(Value lhs, const FP_T rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend Value operator*(const FP_T lhs, Value rhs)
    {
        rhs *= lhs;
        return rhs;
    }

    friend Value& operator/=(Value& lhs, const FP_T rhs)
    {
        lhs._val /= rhs;
        return lhs;
    }

    friend Value operator/(Value lhs, const FP_T rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend Value operator/(const FP_T lhs, Value rhs)
    {
        rhs /= lhs;
        return rhs;
    }

	template<class U1, class U2>
	friend auto operator*(const Value<U1>& lhs, const Value<U2>& rhs)
	-> Value<typename UnitMul<U1,U2>::unit>;

	template<class U1, class U2>
	friend auto operator/(const Value<U1>& lhs, const Value<U2>& rhs)
	-> Value<typename UnitDiv<U1,U2>::unit>;

private:
	FP_T _val;
};

template<class U1, class U2>
auto operator*(const Value<U1>& lhs, const Value<U2>& rhs)
-> Value<typename UnitMul<U1,U2>::unit>
{
	typedef Value<typename UnitMul<U1,U2>::unit> RetType;
	return RetType(lhs._val * rhs._val);
}

template<class U1, class U2>
auto operator/(const Value<U1>& lhs, const Value<U2>& rhs)
-> Value<typename UnitDiv<U1,U2>::unit>
{
	typedef Value<typename UnitDiv<U1,U2>::unit> RetType;
	return RetType(lhs._val / rhs._val);
}

// Typedefs for Basic SI Measurement types
typedef Unit<1,0,0,0,0,0,0> Length;
typedef Unit<0,1,0,0,0,0,0> Mass;
typedef Unit<0,0,1,0,0,0,0> Time;
typedef Unit<0,0,0,1,0,0,0> Current;
typedef Unit<0,0,0,0,1,0,0> Temperature;
typedef Unit<0,0,0,0,0,1,0> Substance;
typedef Unit<0,0,0,0,0,0,1> Luminosity;
typedef Unit<0,0,0,0,0,0,0> Unitless;

// Typedefs for basic SI units
using Meter = Value<Length>;
using Kilogram = Value<Mass>;
using Second = Value<Time>;
using Ampere = Value<Current>;
using Kelvin = Value<Temperature>;
using Mol = Value<Substance>;
using Candela = Value<Luminosity>;
using Scalar = Value<Unitless>;

// Typedefs for more SI measurement types

// Mechanics ============================
using Area = UnitMul<Length,Length>::unit;

using Volume = UnitMul<Area,Length>::unit;

using Velocity = UnitDiv<Length,Time>::unit;

using Acceleration = UnitDiv<Velocity,Time>::unit;

using Jerk = UnitDiv<Acceleration,Time>::unit;

using Radian = Unitless;

using Force = UnitMul<Mass, Acceleration>::unit;
using Newton = Value<Force>;

using Energy = UnitMul<Force,Length>::unit;
using Joule = Value<Energy>;

using Torque = Energy;
using NewtonMeter = Value<Torque>;

using AngularMomentum = UnitMul<Torque,Time>::unit;

using AngularFrequency = UnitDiv<Radian,Time>::unit;

using AngularAcceleration = UnitDiv<AngularFrequency,Time>::unit;

using Work = Energy;

using Power = UnitDiv<Work,Time>::unit;
using Watt = Value<Power>;

using Momentum = UnitMul<Mass,Velocity>::unit;

using Pressure = UnitDiv<Force,Area>::unit;
using Pascal = Value<Pressure>;

using Frequency = UnitDiv<Unitless,Time>::unit;
using Hertz = Value<Frequency>;

using Intensity = UnitDiv<Power,Area>::unit;

// E&M
using Charge = UnitMul<Current,Time>::unit;
using Coulumb = Value<Charge>;

using ElectricFluxDensity = UnitDiv<Charge,Area>::unit;

using Voltage = UnitDiv<Energy,Charge>::unit;
using Volt = Value<Voltage>;

using ElectricField = UnitDiv<Force,Charge>::unit;

using ElectricalResistance = UnitDiv<Voltage,Current>::unit;
using Ohm = Value<ElectricalResistance>;

using Capacitance = UnitDiv<Charge,Voltage>::unit;
using Farad = Value<Capacitance>;

using Permittivity = UnitDiv<Capacitance,Length>::unit;

using Magnetization = UnitDiv<Current,Length>::unit;

using MagneticFlux = UnitMul<Voltage,Time>::unit;
using Weber = Value<MagneticFlux>;

using MagneticFluxDensity = UnitDiv<MagneticFlux,Area>::unit;
using Tesla = Value<MagneticFluxDensity>;

// Thermo??
using Heat = Work;

using HeatCapacity = UnitDiv<Work,Temperature>::unit;

using SpecificHeat = UnitDiv<HeatCapacity,Mass>::unit;

using Entropy = UnitDiv<Energy,Temperature>::unit;

constexpr Meter operator"" m(long double v) {
    return Meter(v);
}

constexpr Kilogram operator"" kg(long double v) {
    return Kilogram(v);
}

constexpr Second operator"" s(long double v) {
    return Second(v);
}

constexpr Ampere operator"" A(long double v) {
    return Ampere(v);
}

constexpr Kelvin operator"" K(long double v) {
    return Kelvin(v);
}

constexpr Mol operator"" mol(long double v) {
    return Mol(v);
}

constexpr Candela operator"" cd(long double v) {
    return Candela(v);
}

namespace constants {

    static const auto c = Value<Velocity>(299792458);
    static const auto G = Value<UnitDiv<UnitDiv<UnitMul<Force,Area>::unit,Mass>::unit,Mass>::unit>(6.67384e-7);
    static const auto h = Value<UnitMul<Energy,Time>::unit>(6.62606957e-34);
    static const auto hbar = decltype(h)(1.054571726e-34);
    
}

}
#endif // UNITS_HPP
