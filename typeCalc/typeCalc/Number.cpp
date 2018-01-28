#include "Value.h"
#include "Number.h"

using namespace typeCalc;

Number::Number(double qty) : _qty(qty) {};

double Number::qty() const {
	return _qty;
}

bool Number::operator==(const Value& val) const {
	const Number* num = dynamic_cast<const Number*>(&val);
	// This class is only equal if val is a Number:
	if (num != nullptr)
		return (qty() == num->qty());
	// If we get something different than Number, then different.
	return false; 
}

void Number::add(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot add a " + operand.typeName() + " to a " + typeName() + ".").c_str());
	else
		_qty += number->qty();
}

void Number::sub(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot subtract a " + operand.typeName() + " from a " + typeName() + ".").c_str());
	else
		_qty -= number->qty();
}

void Number::mult(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot multiply a " + typeName() + " by a " + operand.typeName() + ".").c_str());
	else
		_qty *= number->qty();
}

void Number::div(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot divide a " + typeName() + " by a " + operand.typeName() + ".").c_str());
	else
		_qty /= number->qty();
}
