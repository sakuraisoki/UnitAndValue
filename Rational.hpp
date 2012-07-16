/*
 * Rational.h
 *
 *  Created on: 2010/07/05
 *      Author: sakurai
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#define MAXEXPRESSIONLENGTH 256

#include <string>

namespace hongo {

class Rational {
public:
	Rational(int integer){
		Numerator = integer;
		Denominator = 1;
	}

	Rational(){
		Denominator = 1;
		Numerator = 0;
	}

	Rational(int numer, int denom){
		Denominator = denom;
		Numerator = numer;
		if(Denominator < 0){
			Numerator = -Numerator;
			Denominator = -Denominator;
		}
		Reduce();
	}

	Rational(std::string str){
		*this = strToRational((char*)str.c_str());
	}

	int getNumerator() {
		return Numerator;
	}
	int getDenominator() {
		return Denominator;
	}
	int getIntegerPart() {
		return Numerator / Denominator;
	}
	double getDouble() {
		return (double) Numerator / Denominator;
	}
	std::string getString(){
		char buf[32];
		if(Denominator==1){
			sprintf(buf,"%d",Numerator);
			return std::string(buf);
		}
		else{
			sprintf(buf,"%d/%d",Numerator,Denominator);
			return std::string(buf);
		}
	}

	bool isInteger() {
		if (Numerator / Denominator == 0) {
			return true;
		} else {
			return false;
		}
	}

	friend Rational operator +(Rational rat, int in) {
		Rational tmp(rat.getNumerator() + in * rat.getDenominator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator +(int in, Rational rat) {
		Rational tmp(rat.getNumerator() + in * rat.getDenominator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator -(Rational rat, int in) {
		Rational tmp(rat.getNumerator() - in * rat.getDenominator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator -(int in, Rational rat) {
		Rational tmp(in * rat.getDenominator() - rat.getNumerator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator *(Rational rat, int in) {
		Rational tmp(in * rat.getNumerator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator *(int in, Rational rat) {
		Rational tmp(in * rat.getNumerator(), rat.getDenominator());
		return tmp;
	}
	friend Rational operator /(Rational rat, int in) {
		Rational tmp(rat.getNumerator(), in * rat.getDenominator());
		return tmp;
	}
	friend Rational operator /(int in, Rational rat) {
		Rational tmp(in * rat.getDenominator(), rat.getNumerator());
		return tmp;
	}

	Rational operator + (Rational rat){
		int den1 = this->getDenominator();
		int num1 = this->getNumerator();
		int den2 = rat.getDenominator();
		int num2 = rat.getNumerator();

		Rational ret(den2*num1+den1*num2, den1*den2);
		return ret;
	}

	Rational operator - (Rational rat){
		int den1 = this->getDenominator();
		int num1 = this->getNumerator();
		int den2 = rat.getDenominator();
		int num2 = rat.getNumerator();

		Rational ret(den2*num1-den1*num2, den1*den2);
		return ret;
	}

	Rational operator * (Rational rat){
		int den1 = this->getDenominator();
		int num1 = this->getNumerator();
		int den2 = rat.getDenominator();
		int num2 = rat.getNumerator();
		Rational tmp1(num1,den2);
		Rational tmp2(num2,den1);

		Rational ret(tmp1.getNumerator()*tmp2.getNumerator(), tmp1.getDenominator()*tmp2.getDenominator());
		return ret;
	}

	Rational operator / (Rational rat){
		int den1 = this->getDenominator();
		int num1 = this->getNumerator();
		int den2 = rat.getDenominator();
		int num2 = rat.getNumerator();

		Rational ret(num1*den2, num2*den1);
		return ret;
	}

	Rational operator ^ (int pw){
		int abspw = pw;
		if(pw==0){
			Rational ret(1,1);
			return ret;
		}
		else if(pw < 0){
			abspw = -abspw;
		}

		int den=1,num=1;
		int den0 = this->getDenominator();
		int num0 = this->getNumerator();
		for(int i=0;i<abspw;i++){
			den *= den0;
			num *= num0;
		}
		if(pw < 0){
			int buf = den;
			den = num;
			num = buf;
		}

		Rational ret(num,den);
		return ret;
	}

	void operator = (Rational rat){
		Numerator = rat.getNumerator();
		Denominator = rat.getDenominator();
	}

	void operator = (int numer){
		Numerator = numer;
		Denominator = 1;
	}

	bool operator == (Rational rat){
		if(Numerator == rat.getNumerator() && Denominator == rat.getDenominator()){
			return true;
		}
		else{
			return false;
		}
	}

	bool operator != (Rational rat){
		if(Numerator == rat.getNumerator() && Denominator == rat.getDenominator()){
			return false;
		}
		else{
			return true;
		}
	}

	bool operator < (Rational rat){
		return (this->getDouble() < rat.getDouble());
	}

	bool operator > (Rational rat){
		return (this->getDouble() > rat.getDouble());
	}

	bool operator <= (Rational rat){
		return (this->getDouble() <= rat.getDouble());
	}

	bool operator >= (Rational rat){
		return (this->getDouble() >= rat.getDouble());
	}

	bool operator == (int numer){
		if(Numerator%Denominator==0 && Numerator/Denominator == numer){
			return true;
		}
		else{
			return false;
		}
	}

	void operator ++(int){
		Numerator += Denominator;
	}

	void operator --(int){
		Numerator -= Denominator;
	}

	void operator +=(Rational rat){
		int num = rat.getNumerator();
		int den = rat.getDenominator();
		Numerator = Numerator*den + Denominator*num;
		Denominator *= den;
		Reduce();
	}

	void operator -=(Rational rat){
		int num = rat.getNumerator();
		int den = rat.getDenominator();
		Numerator = Numerator*den - Denominator*num;
		Denominator *= den;
		Reduce();
	}

	void operator *=(Rational rat){
		int num = rat.getNumerator();
		int den = rat.getDenominator();
		Numerator *= num;
		Denominator *= den;
		Reduce();
	}

	void operator /=(Rational rat){
		int num = rat.getNumerator();
		int den = rat.getDenominator();
		Numerator *= den;
		Denominator *= num;
		Reduce();
	}

	Rational operator %(Rational rat){
		int num2 = rat.getNumerator();
		int den2 = rat.getDenominator();
		int num = Numerator*den2;
		int den = Denominator*num2;
		num -= (num%den)*den;
		Rational ret(num,den);
		return ret;
	}

	static Rational strToRational(const char *expstr){
		Rational exp(0,1);
		char str[MAXEXPRESSIONLENGTH];
		strcpy(str,expstr);
		char *start,*pos = str;
		int sign=1;
		start = pos;
		while(*pos!=0){
			if(*pos==' ')strcpy(pos,pos+1);
			if(*pos=='('){
				int pending=1;
				while(pending>0 && *pos!=0){
					pos++;
					if(*pos=='('){
						pending++;
					}
					else if(*pos==')'){
						pending--;
					}
				}
				if(*pos==0 || *(pos-1)=='('){
					return 0;
				}
			}
			else if(*pos=='+'){
				if(pos>start){
					*pos = '\0';
					exp += sign*termToRational(start);
				}
				sign = 1;
				start = pos+1;
			}
			else if(*pos=='-'){
				if(pos>start){
					*pos = 0;
					exp += sign*termToRational(start);
				}
				sign = -1;
				start = pos+1;
			}
			pos++;
		}
		if(pos>start){
			*pos = 0;
			exp += sign*termToRational(start);
		}
		return exp;
	}


	virtual ~Rational(){
	}
public:
	Rational power(int index){
		return Rational(std::pow(this->getNumerator(),(double)index),std::pow(this->getDenominator(),(double)index));
	}

private:
	int Denominator;
	int Numerator;
	void Reduce(){
		int num[2] = {Numerator,Denominator};
		int sign = 1;

		if(num[0] < 0){
			num[0] = -num[0];
			sign = -1;
		}

		if(num[0] == 0){
			Denominator = 1;
			return;
		}
		else if(num[1] == 0 || num[0] == 1 || num[1] == 1){
			return;
		}

		while(num[0]%2==0 && num[1]%2==0){
			num[0] /= 2;
			num[1] /= 2;
		}

		int smaller = 0;
		if(num[0] > num[1]){
			smaller = 1;
		}

	    int eucA = num[smaller];
	    int eucB = num[smaller^1];
	    int eucC;

	    while(eucA%eucB!=0){
	            eucC = eucA % eucB;
	            eucA = eucB;
	            eucB = eucC;
	    }
	    num[0] /= eucB;
	    num[1] /= eucB;

		Numerator = sign*num[0];
		Denominator = num[1];
	}


	static Rational termToRational(const char *termstr){
		Rational term(1,1);
		char str[MAXEXPRESSIONLENGTH];
		strcpy(str,termstr);
		char *start,*pos = str;
		bool divide=false;
		start = pos;
		while(*pos!=0){
			if(*pos==' ')strcpy(pos,pos+1);
			if(*pos=='('){
				start=pos+1;
				int pending=1;
				while(pending>0 && *pos!=0){
					pos++;
					if(*pos=='('){
						pending++;
					}
					else if(*pos==')'){
						pending--;
					}
				}
				if(*pos==0 || pos==start){
					return 0;
				}
				*pos = 0;
				Rational rat = strToRational(start);
				if(divide)rat = 1/rat;
				term *= rat;
				start = pos+2;
			}
			else if(*pos=='*'){
				if(pos>start){
					*pos = 0;
					Rational rat = factorToRational(start);
					if(divide)rat = 1/rat;
					term *= rat;
				}
				divide = false;
				start = pos+1;
			}
			else if(*pos=='/'){
				if(pos>start){
					*pos = 0;
					Rational rat = factorToRational(start);
					if(divide)rat = 1/rat;
					term *= rat;
				}
				divide = true;
				start = pos+1;
			}
			pos++;
		}
		if(pos>start){
			*pos = 0;
			Rational rat = factorToRational(start);
			if(divide)rat = 1/rat;
			term *= rat;
		}
		return term;
		/*
		if(*pos==' ')continue;
		if(*pos>='0' && *pos<='9'){
			numbuf += *pos;
		}
		else if(*pos=='*'){

		}
		*/
	}

	static Rational factorToRational(const char *factorstr){
		Rational factor(0,1);
		char str[MAXEXPRESSIONLENGTH];
		strcpy(str,factorstr);
		int intpart,order=1;
		intpart = 0;
		char *digit,*start,*pos = str;
		start = pos;
		while(*pos!=0){
			if(*pos==' ')strcpy(pos,pos+1);
			if(*pos=='.'){
				intpart = 0;
				digit=pos;
				while(digit--!=start){
					intpart += order*((int)*digit-48);
					order *= 10;
				}
				factor += intpart;
				start = ++pos;
				while(*pos!=0){
					if(*pos < '0' || *pos > '9')return 0;
					pos++;
				}
				intpart = 0;
				order = 1;
				digit = pos;
				while(digit--!=start){
					intpart += order*((int)*digit-48);
					order *= 10;
				}
				Rational flt(intpart,order);
				factor += flt;
				return factor;
			}
			else if(*pos < '0' || *pos > '9'){
				return 0;
			}
			pos++;
		}
		digit = pos;
		while(digit--!=start){
			intpart += order*((int)*digit-48);
			order *= 10;
		}
		factor += intpart;
		return factor;
	}


};

}
#endif /* RATIONAL_H_ */
