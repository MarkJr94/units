// Filename: Units.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef UNITS_HPP
#define UNITS_HPP

#include <cmath>
#include <cstdint>
#include <iostream>

template <int length, int mass, int time, int current, int temp, int amount, int lum>
struct Unit {
	enum { m =length, kg = mass, s = time, A = current, K = temp, mol = amount, cd = lum};
};

template <class u1, class u2>
struct ComputeUnitMul {
	typedef Unit<u1::m + u2::m,u1::kg+u2::kg,u1::s+u2::s,u1::A+u2::A,u1::K+u2::K,u1::mol+u2::mol,u1::cd+u2::cd> unit;
};

template <class u1, class u2>
struct ComputeUnitDiv {
	typedef Unit<u1::m - u2::m,u1::kg-u2::kg,u1::s-u2::s,u1::A-u2::A,u1::K-u2::K,u1::mol-u2::mol,u1::cd-u2::cd> unit;
};

template <int sig>
struct Prefix {
	enum { magnitude = sig };
};

template <class Unit, class Prefix = Prefix<0>, class Numeric = double>
struct Value {
	explicit Value(Numeric val):
		_val(val) {}
	Numeric val() const { return _val; }

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


	template<class U1, class U2, class P, class N>
	friend auto operator*(const Value<U1,P,N>& lhs, const Value<U2,P,N>& rhs)
	-> Value<typename ComputeUnitMul<U1,U2>::unit,P,N>;

	template<class U1, class U2,class P, class N>
	friend auto operator/(const Value<U1,P,N>& lhs, const Value<U2,P,N>& rhs)
	-> Value<typename ComputeUnitDiv<U1,U2>::unit,P,N>;

	template<class P>
	constexpr Value<Unit,P,Numeric> prefix_conv()
	{
		return Value<Unit,P,Numeric>(_val * pow(10,Prefix::magnitude-P::magnitude));
	}


private:
	Numeric _val;
};

template<class U1, class U2, class P, class N>
auto operator*(const Value<U1,P,N>& lhs, const Value<U2,P,N>& rhs)
-> Value<typename ComputeUnitMul<U1,U2>::unit,P,N>
{
	typedef Value<typename ComputeUnitMul<U1,U2>::unit,P,N> RetType;
	return RetType(lhs._val * rhs._val);
}

template<class U1, class U2, class P, class N>
auto operator/(const Value<U1,P,N>& lhs, const Value<U2,P,N>& rhs)
-> Value<typename ComputeUnitDiv<U1,U2>::unit,P,N>
{
	typedef Value<typename ComputeUnitDiv<U1,U2>::unit,P,N> RetType;
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

// Typedefs for metric prefixes
typedef Prefix<-9> nano;
typedef Prefix<-6> micro;
typedef Prefix<-3> milli;
typedef Prefix<-2> centi;
typedef Prefix<-1> deci;
typedef Prefix<0> one;
typedef Prefix<1> deca;
typedef Prefix<2> hecto;
typedef Prefix<3> kilo;
typedef Prefix<6> mega;
typedef Prefix<9> giga;

// Typedefs for basic SI units
typedef Value<Length> Meter;
typedef Value<Mass> Kilogram;
typedef Value<Time> Second;
typedef Value<Current> Ampere;
typedef Value<Temperature> Kelvin;
typedef Value<Substance> Mol;
typedef Value<Luminosity> Candela;

#endif // UNITS_HPP
