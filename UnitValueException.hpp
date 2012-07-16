/*
 * UnitValueException.h
 *
 *  Created on: 2010/07/14
 *      Author: sakurai
 */

#ifndef UNITVALUEEXCEPTION_H_
#define UNITVALUEEXCEPTION_H_

class UnitValueException {
public:
	UnitValueException(){}
	virtual ~UnitValueException(){}
};

class DimensionMismatch : UnitValueException {
public:
	DimensionMismatch(){}
	virtual ~DimensionMismatch(){}
};

class UnknownUnit : UnitValueException {
public:
	UnknownUnit(){}
	virtual ~UnknownUnit(){}
};

class NotConvertibleUnit : UnitValueException {
public:
	NotConvertibleUnit(){}
	virtual ~NotConvertibleUnit(){}
};

class NonZeroDimension : UnitValueException {
public:
	NonZeroDimension(){}
	virtual ~NonZeroDimension(){}
};

//VectorMatrix Exceptions
class NonDimensionMatrix : UnitValueException {
public:
	NonDimensionMatrix(){};
	virtual ~NonDimensionMatrix(){};
};

class TooLargeIndex : UnitValueException {
public:
	TooLargeIndex(){};
	virtual ~TooLargeIndex(){};
};

#endif /* UNITVAL
UEEXCEPTION_H_ */
