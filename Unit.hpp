/*
 * Unit.h
 *
 *  Created on: Oct 12, 2010
 *      Author: sakurai
 */

#ifndef UNIT_H_
#define UNIT_H_

#define MAXSTRSIZE 256

//using namespace std;
#include "UnitValueException.hpp"
#include "Dimension.hpp"
#include "Rational.hpp"
//#include "Mutex.hh"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>


namespace hongo{
class Unit{
public:
	Unit(std::string uname) {
		// TODO Auto-generated constructor stub
		Initialize();
		parseUnit(uname.c_str());
		unitname = uname;
	}

	Unit(std::string uname, double sifactor, std::string siexpression) {
		Initialize();
		Unit un(siexpression);
		*this = un;
		*this *= sifactor;
		unitname = uname;
	}

	Unit(double fac=1.0,Rational massd=0,Rational lend=0,Rational timed=0,Rational tempd=0,Rational ampd=0){
		Initialize();
		SIfactor = fac;
		kg = massd;
		meter = lend;
		sec = timed;
		Kelvin = tempd;
		Ampere = ampd;
		unitname = getSIUnitString();
	}

	virtual ~Unit(){
	}

	void operator =(Unit un) {
		unitname = un.getName();
		SIfactor = un.getSIfactor();
		kg = un.getDimension(1).getDimension();
		meter = un.getDimension(2).getDimension();
		sec = un.getDimension(3).getDimension();
		Kelvin = un.getDimension(4).getDimension();
		Ampere = un.getDimension(5).getDimension();
	}
	void operator =(double fac) {
		Initialize();
		SIfactor = fac;
	}

	void operator *=(Unit un) {
		if (unitname != "") {
			unitname = unitname + "*" + un.getName();
		} else {
			unitname = un.getName();
		}
		SIfactor *= un.getSIfactor();
		kg += un.getDimension(1).getDimension();
		meter += un.getDimension(2).getDimension();
		sec += un.getDimension(3).getDimension();
		Kelvin += un.getDimension(4).getDimension();
		Ampere += un.getDimension(5).getDimension();
	}

	Unit operator *(Unit un) {
		//	unitname = unitname + "*" + un.getUnitName();
		Unit ret = *this;
		ret *= un;
		return ret;
	}

	void operator /=(Unit un) {
		unitname = unitname + "/(" + un.getName() + ")";
		SIfactor /= un.getSIfactor();
		kg -= un.getDimension(1).getDimension();
		meter -= un.getDimension(2).getDimension();
		sec -= un.getDimension(3).getDimension();
		Kelvin -= un.getDimension(4).getDimension();
		Ampere -= un.getDimension(5).getDimension();
	}

	Unit operator /(Unit un) {
		//	unitname = unitname + "*" + un.getUnitName();
		Unit ret = *this;
		ret /= un;
		return ret;
	}

	void operator ^=(Rational powr) {
		char str[64];
		int denom = powr.getDenominator();
		if (denom != 1) {
			sprintf(str, "(%d/%d)", powr.getNumerator(), powr.getDenominator());
		} else {
			sprintf(str, "%d", powr.getNumerator());
		}
		if (unitname != "")
			unitname = "("+unitname+")" + "^" + str;
		SIfactor = pow(SIfactor, powr.getDouble());
		kg *= powr;
		meter *= powr;
		sec *= powr;
		Kelvin *= powr;
		Ampere *= powr;
	}

	void operator *=(double fac) {
		char str[32];
		sprintf(str, "%.1lf", fac);
		unitname = std::string(str) + "*" + unitname;
		SIfactor *= fac;
	}

	void operator /=(double fac) {
		char str[32];
		sprintf(str, "%.1lf", fac);
		unitname = unitname + "/" + std::string(str);
		SIfactor /= fac;
	}

	bool operator ==(Unit un) {
		//Compare only their Dimensions!!!
		return (kg == un.getDimension(1) && meter == un.getDimension(2) && sec == un.getDimension(3) && Kelvin
				== un.getDimension(4) && Ampere == un.getDimension(5));
	}

	bool operator !=(Unit un) {
		//Compare only their Dimensions!!!
		return !(kg == un.getDimension(1) && meter == un.getDimension(2) && sec == un.getDimension(3) && Kelvin
				== un.getDimension(4) && Ampere == un.getDimension(5));
	}
	std::string getName(){return unitname;}

	double getSIfactor(){return SIfactor;}

	std::string getSIUnitString(){
		std::string name="";
		Rational dimension;
		char buf[32];
		dimension=kg.getDimension();
		if(dimension!=0){
			if(dimension.isInteger()){
				if(dimension==1){
					sprintf(buf,"kg");
				}
				else{
					sprintf(buf,"kg^%s",dimension.getString().c_str());
				}
			}
			else{
				sprintf(buf,"kg^(%s)",dimension.getString().c_str());
			}
			name = std::string(buf);
		}
		dimension=meter.getDimension();
		if(dimension!=0){
			if(name!="")name = name + " ";
			if(dimension.isInteger() || dimension < 0){
				if(dimension==1){
					sprintf(buf,"m");
				}
				else{
					sprintf(buf,"m^%s",dimension.getString().c_str());
				}
			}
			else{
				sprintf(buf,"m^(%s)",dimension.getString().c_str());
			}
			name = name + std::string(buf);
		}
		dimension=sec.getDimension();
		if(dimension!=0){
			if(name!="")name = name + " ";
			if(dimension.isInteger() || dimension < 0){
				if(dimension==1){
					sprintf(buf,"s");
				}
				else{
					sprintf(buf,"s^%s",dimension.getString().c_str());
				}
			}
			else{
				sprintf(buf,"s^(%s)",dimension.getString().c_str());
			}
			name = name + std::string(buf);
		}
		dimension=Ampere.getDimension();
		if(dimension!=0){
			if(name!="")name = name + " ";
			if(dimension.isInteger() || dimension < 0){
				if(dimension==1){
					sprintf(buf,"A");
				}
				else{
					sprintf(buf,"A^%s",dimension.getString().c_str());
				}
			}
			else{
				sprintf(buf,"A^(%s)",dimension.getString().c_str());
			}
			name = name + std::string(buf);
		}
		dimension=Kelvin.getDimension();
		if(dimension!=0){
			if(name!="")name = name + " ";
			if(dimension.isInteger() || dimension < 0){
				if(dimension==1){
					sprintf(buf,"K");
				}
				else{
					sprintf(buf,"K^%s",dimension.getString().c_str());
				}
			}
			else{
				sprintf(buf,"K^(%s)",dimension.getString().c_str());
			}
			name = name + std::string(buf);
		}
		return name;
	}


//	Dimension getDimension(){return dimension;}
	Dimension<Rational> getDimension(int index){
		if(index==1){
			return kg;
		}
		else if(index==2){
			return meter;
		}
		else if(index==3){
			return sec;
		}
		else if(index==4){
			return Kelvin;
		}
		else if(index==5){
			return Ampere;
		}
		else{
			Dimension<> dummy;
			return dummy;
		}
	};

	bool isNonDimensional(){return *this==NonDimension;}

//	static void DefineUnit(std::string uname, double sifactor, std::string siexpression){
	void DefineUnit(std::string uname, double sifactor, std::string siexpression){
		Unit newunit(uname, sifactor, siexpression);
		std::vector<Unit>::iterator itr, end = getUnitList().end();
		size_t len = (newunit.getName()).length();
		for (itr = getUnitList().begin(); itr != end; itr++) {
			if (len >= (itr->getName()).length()) {
				getUnitList().insert(itr, newunit);
				break;
			}
		}
		if (itr == end) {
			getUnitList().push_back(newunit);
		}
	}

	std::vector<Unit>& getUnitList(){
		static std::vector<Unit> unitlist;
		return unitlist;
	}

	bool& getIfLoaded(){
		static bool loaded=false;
		return loaded;
	}


private:

	int unitsign;
	//Mutex mutex;
//	static bool loaded;

	std::string unitname;
	double SIfactor;
	Dimension<Rational> kg;
	Dimension<Rational> meter;
	Dimension<Rational> sec;
	Dimension<Rational> Kelvin;
	Dimension<Rational> Ampere;

	static double getprefix(std::string pr) {
		switch (pr[0]) {
		case ('f'):
			return 1.0e-15;
		case ('p'):
			return 1.0e-12;
		case ('n'):
			return 1.0e-9;
		case ('u'):
			return 1.0e-6;
		case ('m'):
			return 1.0e-3;
		case ('c'):
			return 1.0e-2;
		case ('k'):
			return 1.0e+3;
		case ('M'):
			return 1.0e+6;
		case ('G'):
			return 1.0e+9;
		case ('T'):
			return 1.0e+12;
		case ('P'):
			return 1.0e+15;
		case ('E'):
			return 1.0e+18;
		}
		return -1;
	};

	void Initialize() {
		unitname = "";
		SIfactor = 1.0;
		kg.setDimensionName("kg");
		meter.setDimensionName("meter");
		sec.setDimensionName("sec");
		Kelvin.setDimensionName("Kelvin");
		Ampere.setDimensionName("Ampere");
		if (!getIfLoaded()) {
			//mutex.lock();
			getIfLoaded() = true;
			LoadStandardUnits();
			//mutex.unlock();
		}
	}

	void LoadStandardUnits() {
		//	unitlist.push_back(NonDimension);
		DefineUnit("sec", 1, "s");
		DefineUnit("second", 1, "s");
		DefineUnit("min", 60, "s");
		DefineUnit("Pa", 1, "kg/m/s^2");
		DefineUnit("atm", 101325, "kg/m/s^2");
		DefineUnit("h", 3600, "s");
		DefineUnit("hour", 3600, "s");
		DefineUnit("hr", 3600, "s");
		DefineUnit("d", 86400, "s");
		DefineUnit("day", 86400, "s");
		DefineUnit("yr", 31536000, "s");
		DefineUnit("year", 31536000, "s");
		DefineUnit("Hz", 1.0, "/s");
		DefineUnit("eV", 1.60217646e-19, "kg*m^2/s^2");
		DefineUnit("erg", 1.0e-7, "kg*m^2/s^2");
		DefineUnit("J", 1.0, "kg*m^2/s^2");
		DefineUnit("W", 1.0, "kg*m^2/s^3");
		DefineUnit("N", 1.0, "kg*m/s^2");
		DefineUnit("cal", 4.1868, "kg*m^2/s^2");
		DefineUnit("l", 0.001, "m^3");
		DefineUnit("Ang", 1e-10, "m");
		DefineUnit("oz", 0.028349523125, "kg");
		DefineUnit("dyn", 1e-5, "kg*m/s^2");
		DefineUnit("mi", 1609.344, "m");
		DefineUnit("mile", 1609.344, "m");
		DefineUnit("yd", 0.9144, "m");
		DefineUnit("in", 0.0254, "m");
		DefineUnit("ft", 0.3048, "m");
		DefineUnit("gal", 0.003785411784, "m^3");
		DefineUnit("lb", 0.45359237, "kg");
		DefineUnit("t", 1000, "kg");
		DefineUnit("ton", 1000, "kg");
		DefineUnit("pc", 3.08568e+16, "m");
		DefineUnit("ly", 9.46073e+15, "m");
		DefineUnit("AU", 1.49598e+11, "m");
		DefineUnit("k_b", 1.38065e-23, "kg*m^2/s^2/K");
		DefineUnit("C", 1.0, "A*s");
		DefineUnit("V", 1.0, "kg*m^2/s^3/A");
		DefineUnit("F", 1.0, "/kg/m^2*s^4*A^2");
		DefineUnit("T", 1.0, "kg/s^2/A");
		DefineUnit("G", 1.0e-4, "kg/s^2/A");
		DefineUnit("e", 1.60218e-19, "A*s");
		DefineUnit("Ohm", 1.0, "kg*m^2/s^3/A^2");
		DefineUnit("H", 1.0, "kg*m^2/s^2/A^2");

		DefineUnit("Msun", 1.9891e30, "kg");
	}

	void CopyDimensions(Unit un) {
		kg = un.getDimension(1).getDimension();
		meter = un.getDimension(2).getDimension();
		sec = un.getDimension(3).getDimension();
		Kelvin = un.getDimension(4).getDimension();
		Ampere = un.getDimension(5).getDimension();
	}

	bool parseUnit(const char* ustr) {
		char *pos, str[MAXSTRSIZE];
		strcpy(str, ustr);
		pos = str;
		while (*pos == ' ')
			pos++;
		if ((*pos >= '0' && *pos <= '9') || *pos == '.' || *pos == '|') {
			char buf, *start = pos++;
			while ((*pos >= '0' && *pos <= '9') || *pos == '.' || *pos == '|' || *pos == ' ')
				pos++;
			buf = *pos;
			*pos = '\0';
			SIfactor = Rational::strToRational(start).getDouble();
			*pos = buf;
		}
		*this *= termToUnit(pos);
		return true;
	}

	Unit termToUnit(const char* ustr) {
		Unit term;
		bool divide = false;
		char *pos, *start, str[MAXSTRSIZE];
		strcpy(str, ustr);
		pos = str;
		start = pos;
		while (*pos != '\0') {
			if (*pos == '(') {
				start = pos + 1;
				int pending = 1;
				while (pending > 0 && *pos != 0) {
					pos++;
					if (*pos == '(') {
						pending++;
					} else if (*pos == ')') {
						pending--;
					}
				}
				if (*pos == 0 || *(pos - 1) == '(') {
					UnknownUnit error;
					throw error;
				}
				*pos = 0;
				if ((*start >= '0' && *start <= '9') || *start == '.') {
					term *= Rational::strToRational(start).getDouble();
				} else {
					term *= termToUnit(start);
				}
				start = pos + 1;
			} else if (*pos == ' ') {
				if (*(pos - 1) == '*' || *(pos - 1) == '/' || *(pos - 1) == '^') {
					char *newpos = pos;
					while (*newpos == ' ')
						newpos++;
					strcpy(pos, newpos);
					pos = pos - 1;
				} else {
					char *newpos = pos;
					while (*newpos == ' ')
						newpos++;
					if (*newpos == '*' || *newpos == '/' || *newpos == '^') {
						strcpy(pos, newpos);
						pos = pos - 1;
					} else {
						strcpy(pos + 1, newpos);
						*pos = '\0';
						Unit un = getNumberOrUnit(start);
						if (divide)
							un ^= -1;
						term *= un;
						*pos = '*';
						divide = false;
						start = pos + 1;
					}
				}
			} else if (*pos == '*') {
				*pos = '\0';
				Unit un = getNumberOrUnit(start);
				*pos = '*';
				if (divide)
					un ^= -1;
				term *= un;
				divide = false;
				start = pos + 1;
			} else if (*pos == '/') {
				*pos = '\0';
				Unit un = getNumberOrUnit(start);
				*pos = '/';
				if (divide)
					un ^= -1;
				term *= un;
				divide = true;
				start = pos + 1;
			} else if (*pos == '^') {
				pos++;
				while (*pos == ' ')
					pos++;
				if (*pos == '(') {
					int pending = 1;
					while (pending > 0 && *pos != 0) {
						pos++;
						if (*pos == '(') {
							pending++;
						} else if (*pos == ')') {
							pending--;
						}
					}
					if (*pos == '\0' || *(pos - 1) == '(') {
						UnknownUnit error;
						throw error;
					}
				} else {
					while (*pos != '/' && *pos != '*' && *pos != ' ' && *pos != '(' && *pos != '\0')
						pos++;
					pos = pos - 1;
				}
			}
			pos++;
		}
		if (pos > start) {
			Unit un = getNumberOrUnit(start);
			if (divide)
				un ^= -1;
			term *= un;
		}
		return term;
	}

	Unit getNumberOrUnit(const char* str) {
		Unit un;
		if ((*str >= '0' && *str <= '9') || *str == '.' || *str == '|') {
			un = Rational::strToRational(str).getDouble();
		} else {
			un = factorToUnit(str);
		}
		return un;
	}

	Unit factorToUnit(const char* ustr) {
		Unit factor;
		bool powered = false;
		std::string unitname, buf = ustr;
		char *pos, *uendpos, *start, str[MAXSTRSIZE];
		strcpy(str, ustr);
		pos = str;
		while (*pos == ' ')
			pos++;
		start = pos;
		while (*pos != '\0' && *pos != '^')
			pos++;
		uendpos = pos - 1;
		if (*pos == '^') {
			while (*uendpos == ' ')
				uendpos--;
			*(++uendpos) = '\0';
			powered = true;
		}
		unitname = start;
		std::vector<Unit>::iterator itr, end = getUnitList().end();
		size_t upos = 0;
		for (itr = getUnitList().begin(); itr != end; itr++) {
			upos = unitname.rfind(itr->getName());
			if (upos == std::string::npos)
				continue;
			if (upos > 1) {
				UnknownUnit error;
				throw error;
			} else if (upos == 0) {
				factor = *itr;
				break;
			} else if (upos == 1) {
				factor = *itr;
				factor *= getprefix(unitname);
				break;
			}
		}
		if (itr == end) {
			factor = getSIUnit(unitname);
		}
		if (powered) {
			while (*(++pos) == ' ')
				;
			Rational index = Rational::strToRational(pos);
			factor ^= index;
		}
		return factor;
	}

	Unit getSIUnit(std::string uname) {
		Unit ret;
		double pref = 1.0;
		size_t index, len = uname.length();
		if (len > 2) {
			UnknownUnit error;
			throw error;
		}
		index = len - 1;
		if (uname[index] == 'g') {
			pref /= 1000.0;
			ret = Unit(1.0, 1, 0, 0, 0, 0);
		} else if (uname[index] == 'm') {
			ret = Unit(1.0, 0, 1, 0, 0, 0);
		} else if (uname[index] == 's') {
			ret = Unit(1.0, 0, 0, 1, 0, 0);
		} else if (uname[index] == 'K') {
			ret = Unit(1.0, 0, 0, 0, 1, 0);
		} else if (uname[index] == 'A') {
			ret = Unit(1.0, 0, 0, 0, 0, 1);
		}
		if (len == 2) {
			pref *= getprefix(uname);
		}
		ret *= pref;
		return ret;
	}

	static const Unit NonDimension;
};
}

#endif /* UNIT_H_ */
