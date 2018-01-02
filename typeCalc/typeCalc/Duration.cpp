#include "Value.h"
#include "CharHelpers.h"

using namespace typeCalc;


Duration::Duration(const std::string& text) {

	std::string qtyStr;
	int implied_mult = 0; // Used to store the multiplier to use for the last value if no last unit is entered (ex: 5h30 vs 5h30m)
	_qty = 0;
	for (auto c = text.begin(); c != text.end(); c++) {
		// We start by accumulating the string for the number until we find a unit symbol:
		if (IS_DIGIT(*c)) {
			qtyStr += *c; // Append the char to the qty string.
			continue;
		}
		// Parse the unit:
		switch (*c) {
		case 'h': // We have hours, accumulate the last number times 3600
			if (qtyStr.length() == 0)
				throw Error::INVALID_VALUE;
			_qty += 3600 * atoi(qtyStr.c_str());
			implied_mult = 60; // We just parsed an hour, the next value is implied minutes 
			break;
		case 'm':  // We have minutes, accumulate the last number times 60
			if (qtyStr.length() == 0)
				throw Error::INVALID_VALUE;
			_qty += 60 * atoi(qtyStr.c_str());
			implied_mult = 1; // We just parsed minutes, the next value is implied seconds 
			break;
		case 's': // We have seconds, accumulate the last number directly
			if (qtyStr.length() == 0)
				throw Error::INVALID_VALUE;
			_qty += atoi(qtyStr.c_str());
			break;
		default:
			throw Error::INVALID_VALUE;
		}
		qtyStr = "";

	}
	if (implied_mult == 0) // If the implied mult is zero, it means we just parsed a number, not a duration. Throw:
		throw Error::INVALID_VALUE;

	if (qtyStr.length() > 0) // we have remaining value, add it using the implied multiplier:
		_qty += atoi(qtyStr.c_str()) * implied_mult;
}

Duration::Duration(int seconds) : _qty(seconds) {}

/* From: typeCalc::Value */
double Duration::qty() const {
	return _qty;
}

std::unique_ptr<Value> Duration::eval(const Operator op) const {
	throw Error::OPER_NOT_IMPL;
}

std::unique_ptr<Value> Duration::eval(const Operator op, const Number* const val2) const {
	switch (op) {
	case Operator::MULT:
		return std::unique_ptr<Duration>(new Duration(_qty * val2->qty()));
	case Operator::DIV:
		return std::unique_ptr<Duration>(new Duration(_qty / val2->qty()));
	default:
		throw Error::OPER_NOT_IMPL;
	}
}

std::unique_ptr<Value> Duration::eval(const Operator op, const Duration* const val2) const {
	switch (op) {
	case Operator::PLUS:
		return std::unique_ptr<Duration>(new Duration(_qty + val2->qty()));
	case Operator::MINUS:
		return std::unique_ptr<Duration>(new Duration(_qty - val2->qty()));
	default:
		throw Error::OPER_NOT_IMPL;
	}
}

bool Duration::operator==(const Value& val) const {
	// This class is only equal if val is a Duration:
	try {
		const Duration* num = dynamic_cast<const Duration*>(&val);
		return (qty() == num->qty());
	}
	catch (...) {
		// If we get something different than Duration, then different.
		return false;
	}
}
