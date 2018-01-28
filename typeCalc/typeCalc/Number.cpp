#include "Value.h"
#include "Number.h"
#include "Duration.h"

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

std::unique_ptr<Value> Number::add(const Value& operand) const {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot add a " + operand.typeName() + " to a " + typeName() + ".").c_str());
	else
		return std::unique_ptr<Value>(new Number(_qty + number->qty()));
}

std::unique_ptr<Value> Number::sub(const Value& operand) const {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot subtract a " + operand.typeName() + " from a " + typeName() + ".").c_str());
	else
		return std::unique_ptr<Value>(new Number(_qty - number->qty()));
}

std::unique_ptr<Value> Number::mult(const Value& operand) const {
	// Number mult with number:
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number != nullptr) {
		return std::unique_ptr<Value>(new Number(_qty * number->qty()));
	}
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration != nullptr) {
		return std::unique_ptr<Value>(new Duration((int)(_qty * duration->qty())));
	}
	throw std::exception(("Cannot multiply a " + typeName() + " by a " + operand.typeName() + ".").c_str());
}

std::unique_ptr<Value> Number::div(const Value& operand) const {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr)
		throw std::exception(("Cannot divide a " + typeName() + " by a " + operand.typeName() + ".").c_str());
	else
		return std::unique_ptr<Value>(new Number(_qty / number->qty()));
}

std::string Number::asString() const {
	return std::move(std::to_string(_qty));
}

std::string Number::typeName() const {
	return std::string("Number");
}
