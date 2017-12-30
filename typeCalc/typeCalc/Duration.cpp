#include "Value.h"

using namespace typeCalc;

Duration::Duration(const std::string& text) {
	// TODO: Implement Duration parsing
	throw Error::INVALID_VALUE;
}

/* From: typeCalc::Value */
double Duration::qty() const {
	return _qty;
}

std::unique_ptr<Value> Duration::eval(const Operator op) const {
	throw Error::OPER_NOT_IMPL;
}

std::unique_ptr<Value> Duration::eval(const Operator op, const Number* const val2) const {
	throw Error::OPER_NOT_IMPL;
}


std::unique_ptr<Value> Duration::eval(const Operator op, const Duration* const val2) const {
	throw Error::OPER_NOT_IMPL;
}

bool Duration::operator==(const Value& val) const {
	// This class is only equal if val is a Number:
	try {
		const Duration* num = dynamic_cast<const Duration*>(&val);
		return (qty() == num->qty());
	}
	catch (...) {
		// If we get something different than Number, then different.
		return false;
	}
}
