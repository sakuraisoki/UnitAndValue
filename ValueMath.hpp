/*
 * ValueMath.h
 *
 *  Created on: 2010/12/30
 *      Author: Sakurai
 */

#ifndef VALUEMATH_H_
#define VALUEMATH_H_

#include "Value.hpp"
#include "UnitValueException.hpp"

#include <cmath>

namespace hongo{

class ValueMath {
public:
	ValueMath();
	virtual ~ValueMath();

	static Value vsqrt(Value val){
		Unit un = val.getUnit();
		Rational rat(1,2);
		double value = sqrt(val.getValueIn(un));
		un ^= rat;
		Value ret(value,un);
		return ret;
	}

	static Value vpow(Value val, Rational index){
		Unit un = val.getUnit();
		double value = pow(val.getValueIn(un),index.getDouble());
		un ^= index;
		Value ret(value,un);
		return ret;
	}

	static Value vsin(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = sin(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	static Value vcos(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = cos(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	static Value vtan(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = tan(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	static Value vsinh(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = sinh(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	static Value vcosh(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = cosh(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	static Value vtanh(Value val){
		Unit un = val.getUnit();
		if(!un.isNonDimensional()){
			NonZeroDimension error;
			throw error;
		}
		double value = tanh(val.getValueIn(un));
		Value ret(value,un);
		return ret;
	}

	friend Value operator ^ (Value val, Rational index){
		Value tmp = vpow(val,index);
		return tmp;
	}
};
}

#endif /* VALUEMATH_H_ */
