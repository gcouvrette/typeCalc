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

bool Value::operator==(const Value &val2) const {
	return false;
}

double Value::qty() const
{
	return _qty;
}

Value::Type Value::type() const
{
	return NUMBER;
}
