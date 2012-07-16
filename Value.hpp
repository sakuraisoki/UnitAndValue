/*
 * Value.h
 *
 *  Created on: Oct 12, 2010
 *      Author: sakurai
 */

#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Unit.hpp"
#include "UnitValueException.hpp"

namespace hongo{
class Value {
public:
	Value(double val=0.0, std::string unitname=""){
		// TODO Auto-generated constructor stub
		try{
			Unit un(unitname);
			unit = un;
		}
		catch(...){
			std::cout << "No such unit" << std::endl;
			exit(1);
		}
		initialvalue = val;
		SIvalue = val;
		SIvalue *= unit.getSIfactor();
	}

	Value(double val, Unit un){
		initialvalue = val;
		SIvalue = val*un.getSIfactor();
		unit = un;
	}

	virtual ~Value(){
	}

	double getValueIn(std::string outunit){
		double ret = SIvalue;
		Unit conv;
		try{
			Unit un(outunit);
			conv = un;
		}
		catch(...){
			std::cout << "No such unit" << std::endl;
			exit(1);
		}
		if(unit!=conv){
			DimensionMismatch error;
			throw error;
		}
		ret /= conv.getSIfactor();
		return ret;
	}

	double getValueIn(Unit outunit){
		double ret = SIvalue;
		ret /= outunit.getSIfactor();
		return ret;
	}

	double getValueInSI(){return SIvalue;};

	std::string getValueWithUnit(unsigned int precision=4){
		std::string valuewithunit,format="%.";
		char buf[64];
		sprintf(buf,"%d",precision);
		format = format + std::string(buf) + "E |%s|";
		sprintf(buf,format.c_str(),getValueIn(unit),unit.getName().c_str());
		valuewithunit = buf;
		return valuewithunit;
	}

	double getInitialValue(){return initialvalue;};

	std::string getUnitName(){return unit.getName();}

	void setUnit(std::string unitname){
		Unit newunit;
		try{
			Unit un(unitname);
			newunit = un;
		}
		catch(...){
			std::cout << "No such unit" << std::endl;
			exit(1);
		}
		double newvalue = getValueIn(newunit);
		*this = Value(newvalue,newunit);
	}

	void setUnit(Unit newunit){
		double newvalue = getValueIn(newunit);
		*this = Value(newvalue,newunit);
	}

	Unit getUnit(){return unit;};

	void reduceUnit(){
		Rational kgdim = unit.getDimension(1).getDimension();
		Rational meterdim = unit.getDimension(2).getDimension();
		Rational secdim = unit.getDimension(3).getDimension();
		Rational Amperedim = unit.getDimension(4).getDimension();
		Rational Kelvindim = unit.getDimension(5).getDimension();
		Unit siunit(1.0,kgdim,meterdim,secdim,Amperedim,Kelvindim);
		unit = siunit;
	}

	bool isNonDimensional(){return unit.isNonDimensional();};

	friend Value operator + (Value val, double db){
		if(!val.isNonDimensional())throw UnitValueException();
		Value ret = Value(val.getValueInSI()+db);
		return ret;
	}
	friend Value operator + (double db, Value val){
		if(!val.isNonDimensional())throw UnitValueException();
		Value ret = Value(val.getValueInSI()+db);
		return ret;
	}

	friend Value operator - (Value val, double db){
		if(!val.isNonDimensional())throw UnitValueException();
		Value ret = Value(val.getValueInSI()-db);
		return ret;
	}
	friend Value operator - (double db, Value val){
		if(!val.isNonDimensional())throw UnitValueException();
		Value ret = Value(-val.getValueInSI()+db);
		return ret;
	}

	Value operator + (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		Value ret(getValueIn(unit)+VAL.getValueIn(unit),unit);
		return ret;
	}
	void operator += (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		Value ret(getValueIn(unit)+VAL.getValueIn(unit),unit);
		*this = ret;
	}
	Value operator - (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		Value ret(getValueIn(unit)-VAL.getValueIn(unit),unit);
		return ret;
	}
	void operator -= (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		Value ret(getValueIn(unit)-VAL.getValueIn(unit),unit);
		*this = ret;
	}
	Value operator * (Value VAL){
		Unit newu = unit*VAL.getUnit();
		Value ret(SIvalue*VAL.getValueInSI()/newu.getSIfactor(),newu);
		return ret;
	}
	void operator *= (Value VAL){
		unit *= VAL.getUnit();
		initialvalue *= VAL.getInitialValue();
		SIvalue *= VAL.getValueInSI();
	}
	friend Value operator * (Value val, double db){
		Value tmp(val.getInitialValue()*db,val.getUnit());
		return tmp;
	}
	friend Value operator * (double db, Value val){
		Value tmp(val.getInitialValue()*db,val.getUnit());
		return tmp;
	}

	Value operator / (Value VAL){
		Unit newu = unit/VAL.getUnit();
		Value ret(SIvalue/VAL.getValueInSI()/newu.getSIfactor(),newu);
		return ret;
	}
	void operator /= (Value VAL){
		unit /= VAL.getUnit();
		initialvalue /= VAL.getInitialValue();
		SIvalue /= VAL.getValueInSI();
	}
	friend Value operator / (Value val, double db){
		Value tmp(val.getInitialValue()/db,val.getUnit());
		return tmp;
	}
	friend Value operator / (double db, Value val){
		Value tmp(db);
		tmp = tmp/val;
		return tmp;
	}
	void operator = (Value VAL){
		initialvalue = VAL.getInitialValue();
		SIvalue = VAL.getValueInSI();
		unit = VAL.getUnit();
	}

	bool operator == (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()==VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

	bool operator != (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()!=VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

	bool operator > (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()>VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

	bool operator >= (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()>=VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

	bool operator < (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()<VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

	bool operator <= (Value VAL){
		if(unit != VAL.getUnit()){
			DimensionMismatch error;
			throw error;
		}
		if(this->getValueInSI()<=VAL.getValueInSI()){
			return true;
		}else{
			return false;
		}
	}

private:
//	void Initialize();

	double initialvalue;
	double SIvalue;
	Unit unit;
};

}
#endif /* VALUE_H_ */
