/*
 * Dimension.h
 *
 *  Created on: Nov 18, 2010
 *      Author: sakurai
 */

#ifndef DIMENSION_H_
#define DIMENSION_H_

//#include "Rational.h"

#include <iostream>
#include <string>

#include "Rational.hpp"

namespace hongo {
template<class Type = Rational>
class Dimension{
public:
	Dimension(std::string name = "", Type dim = 0){
		// TODO Auto-generated constructor stub
		dimensionName = name;
		dimension = dim;
	}

	virtual ~Dimension(){
		// TODO Auto-generated destructor stub
	}

	Type getDimension(){
		return dimension;
	}
	std::string getDimensionName(){
		return dimensionName;
	}

	void setDimensionName(std::string name){
		dimensionName = name;
	}

	void operator =(Type dim){
		dimension = dim;
	}

	bool operator ==(Dimension<Type> dim){
		return (dimension==dim.getDimension())&&(dimensionName==dim.getDimensionName());
	}

	bool operator <(Dimension<Type> dim){
		return (dimension<dim.getDimension());
	}

	bool operator >(Dimension<Type> dim){
		return (dimension>dim.getDimension());
	}

	bool operator <=(Dimension<Type> dim){
		return (dimension<=dim.getDimension());
	}

	bool operator >=(Dimension<Type> dim){
		return (dimension>=dim.getDimension());
	}

	void operator ++(int){
		dimension++;
	}

	void operator --(int){
		dimension--;
	}

	void operator +=(Type dim){
		dimension += dim;
	}

	void operator -=(Type dim){
		dimension -= dim;
	}

	void operator *=(Type dim){
		dimension *= dim;
	}

	void operator /=(Type dim){
		dimension /= dim;
	}

	Type operator %(Type dim){
		return dimension%dim;
	}

	friend void operator +(Dimension dim, Type num){
		dim += num;
	}
	friend void operator +(Type num, Dimension dim){
		dim += num;
	}
	friend void operator -(Dimension dim, Type num){
		dim -= num;
	}
	friend void operator -(Type num, Dimension dim){
		dim -= num;
	}
	friend void operator *(Dimension dim, Type num){
		dim *= num;
	}
	friend void operator *(Type num, Dimension dim){
		dim *= num;
	}
	friend void operator /(Dimension dim, Type num){
		dim /= num;
	}
	Dimension operator +(Dimension dim);
	Dimension operator -(Dimension dim);
	Dimension operator *(Dimension dim);
	Dimension operator /(Dimension dim);
	Dimension operator %(Dimension dim);

private:
	Type dimension;
	std::string dimensionName;
};
}
#endif /* DIMENSION_H_ */

