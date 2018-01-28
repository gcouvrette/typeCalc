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
	const Duration* num = dynamic_cast<const Duration*>(&val);
	// This class is only equal if val is a Duration:
	if (num != nullptr)
		return (qty() == num->qty());
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
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot multiply " + typeName() + " with " + operand.typeName() + ".").c_str());
	}
	else {
		return std::unique_ptr<Value>(new Duration(_qty * number->qty()));
	}
}

std::unique_ptr<Value> Duration::div(const Value& operand) const {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot divide " + typeName() + " with " + operand.typeName() + ".").c_str());
	}
	else {
		return std::unique_ptr<Value>(new Duration(_qty / number->qty()));
	}
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
