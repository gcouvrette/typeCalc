#include "typeCalc.h"
#include "CharHelpers.h"

using namespace typeCalc;

Value::Value(std::string text) {
	// We do not allow empty values. Throws an exception if the text is empty:
	if (text.empty())
		throw Value::Error::EMPTY_TEXT;

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

typeCalc::Value::Value(double qty)
{
	_qty = qty;
}

typeCalc::Value::Value(const Value & value)
{
	_qty = value._qty;
}

bool Value::operator==(const Value &val2) const {
	return qty() == val2.qty() &&
		type() == val2.type();
}

double Value::qty() const
{
	return _qty;
}

Value::Type Value::type() const
{
	return NUMBER;
}

Value typeCalc::Value::eval(Operator op, const Value& val2) const
{
	// For now, we implement as if we are NUMBER by default, TODO: Refactor Value in subclasses,
	// and overload eval per type, ex: DurationValue::eval(op, val), NumverValue::eval(op, val) 
	switch (op) {
	case PLUS:
		return Value(qty() + val2.qty());
	case MINUS:
		return Value(qty() - val2.qty());
	case MULT:
		return Value(qty() * val2.qty());
	case DIV:
		return Value(qty() / val2.qty());
	default:
		throw OPER_NOT_IMPL;
	}
}
