#include "Duration.h"
#include "Number.h"
#include <exception>

using namespace typeCalc;

Duration::Duration(int seconds): _qty(seconds) {
}

Duration::Duration(unsigned int hours /* = 0 */, unsigned int minutes /* = 0 */, unsigned int seconds /* = 0 */, bool isNeg /* = false */) {
	_qty = 0;
	_qty += 3600 * hours;
	_qty += 60 * minutes;
	_qty += seconds;
	if (isNeg)
		_qty *= (-1);
}

/* From: typeCalc::Value */
double Duration::qty() const {
	return _qty;
}

bool Duration::operator==(const Value& val) const {
	const Duration* duration = dynamic_cast<const Duration*>(&val);
	// This class is only equal if val is a Duration:
	if (duration != nullptr)
		return (qty() == duration->qty());
	// If we get something different than Duration, then different.
	return false;
}

std::unique_ptr<Value> Duration::add(const Value& operand) const {
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot add " + operand.typeName() + " to " + typeName() + ".").c_str());
	}
	else {
		return std::unique_ptr<Value>(new Duration(_qty + duration->qty()));
	}
}

std::unique_ptr<Value> Duration::sub(const Value& operand) const {
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot subtract " + operand.typeName() + " from " + typeName() + ".").c_str());
	}
	else {
		return std::unique_ptr<Value>(new Duration(_qty - duration->qty()));
	}
}

std::unique_ptr<Value> Duration::mult(const Value& operand) const {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr) {
		// We do not have a number; throw invalid operation error:
		throw std::exception(("Cannot multiply " + typeName() + " with " + operand.typeName() + ".").c_str());
	}
	else {
		return std::unique_ptr<Value>(new Duration(_qty * number->qty()));
	}
}

std::unique_ptr<Value> Duration::div(const Value& operand) const {
	// Do not allow division by zero for any data type
	if (operand.isZero())
		throw std::exception(("Cannot divide " + typeName() + " (" + asString() + ") by zero.").c_str());
	// Duration division can be with a number (ex: 8h00 / 2 == 4h00),
	// Or it can be divided by a duration to get a number, ex: 8h00 / 0h30 == 16)

	// First, test with a number division: 
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number != nullptr) {
		return std::unique_ptr<Value>(new Duration(_qty / number->qty()));
	}
	// Then, try with a duration:
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration != nullptr) {
		return std::unique_ptr<Value>(new Number(_qty / duration->qty()));
	}
	// We do not have a valid data type; throw invalid operation error:
	throw std::exception(("Cannot divide " + typeName() + " with " + operand.typeName() + ".").c_str());
}


std::string Duration::asString() const {
	std::string result;
	int absoluteQty = (_qty < 0 ? -1 * _qty : _qty);
	int hours = absoluteQty / 3600;
	int mins = (absoluteQty - ((int)hours * 3600)) / 60;
	int secs = (absoluteQty - ((int)hours * 3600) - ((int)mins * 60));

	if (_qty < 0)
		result += "-";
	if (hours > 0)
		result += std::to_string(hours) + "h";
	if (mins > 0)
		result += std::to_string(mins) + "m";
	if (secs > 0 || absoluteQty < 60)
		result += std::to_string(secs) + "s";

	return std::move(result);
}

std::string Duration::typeName() const {
	return std::string("Duration");
}

bool Duration::isZero() const {
	return (_qty == 0);
}
