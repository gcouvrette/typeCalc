#include "Duration.h"
#include "Number.h"
#include <exception>

using namespace typeCalc;

Duration::Duration(int seconds) 
	: _qty(seconds) {}

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

void Duration::add(const Value& operand) {
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot add " + operand.typeName() + " to " + typeName() + ".").c_str());
	}
	else {
		_qty += duration->qty();
	}
}

void Duration::sub(const Value& operand) {
	const Duration* duration = dynamic_cast<const Duration*>(&operand);
	if (duration == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot subtract " + operand.typeName() + " from " + typeName() + ".").c_str());
	}
	else {
		_qty -= duration->qty();
	}
}

void Duration::mult(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot multiply " + typeName() + " with " + operand.typeName() + ".").c_str());
	}
	else {
		_qty *= number->qty();
	}
}

void Duration::div(const Value& operand) {
	const Number* number = dynamic_cast<const Number*>(&operand);
	if (number == nullptr) {
		// We do not have a duration; throw invalid operation error:
		throw std::exception(("Cannot divide " + typeName() + " with " + operand.typeName() + ".").c_str());
	}
	else {
		_qty /= number->qty();
	}
}
