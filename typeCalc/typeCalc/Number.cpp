#include "Value.h"
#include "CharHelpers.h"

using namespace typeCalc;

Number::Number(const std::string& text) {
	// Start by extracting the quantity:
	std::string qtyStr = "";
	int digit_mode = false; // A dot was found and we are evaluating decimals
	auto c = text.begin();

	// First of all, accept the first char if is is a '-'
	if (IS_NEG(*c)) {
		qtyStr += *c;
		c++;
	}

	for (; c != text.end(); c++) {
		// Either we get a dot, or a number. Anything else is considered not a proper value.
		if (IS_DOT(*c)) {
			if (!digit_mode)
				digit_mode = true; // We are now in digit mode.
			else
				throw Value::Error::MULTIPLE_DECIMAL_POINTS;
		}
		else if (!IS_DIGIT(*c))
			break;

		qtyStr += *c; // Append the char to the qty string.
	}
	_qty = atof(qtyStr.c_str());
}

Number::Number(double qty) : _qty(qty) {};


double Number::qty() const {
	return _qty;
}

std::unique_ptr<Value> Number::eval(const Operator op) const {
	throw Error::OPER_NOT_IMPL;
}

std::unique_ptr<Value> Number::eval(const Operator op, const Duration* const val2) const {
	throw Error::OPER_NOT_IMPL;
}

std::unique_ptr<Value> Number::eval(const Operator op, const Number* const val2) const {
	Number* number = nullptr;
	switch (op) {
	case PLUS:
		number = new Number(qty() + val2->qty());
		break;
	case MINUS:
		number = new Number(qty() - val2->qty());
		break;
	case MULT:
		number = new Number(qty() * val2->qty());
		break;
	case DIV:
		number = new Number(qty() / val2->qty());
		break;
	default:
		throw OPER_NOT_IMPL;
	}
	return std::unique_ptr<Value>(number);
}

bool Number::operator==(const Value& val) const {
	// This class is only equal if val is a Number:
	try {
	const Number* num = dynamic_cast<const Number*>(&val);
	return (qty() == num->qty());
	}
	catch (...) {
		// If we get something different than Number, then different.
		return false; 
	}
}
