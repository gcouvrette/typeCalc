#include "Value.h"

using namespace typeCalc;

std::unique_ptr<Value> Value::fromString(const std::string& text) {
	// Pre-processor to prevent having to copy for each value type:
	#define TRY_BUILD(T) try {return std::unique_ptr<Value>(new T(text)); } catch(...){}
	// We receive a text value. Try to construct it as each data type existing and return it if it works:
	// First: We do not allow empty values. Throws an exception if the text is empty:
	if (text.empty())
		throw Value::Error::EMPTY_TEXT;
	// Try to build a data type using this value:
	TRY_BUILD(Number);
	TRY_BUILD(Duration);
	// Nothing matches. Invalid value.
	throw Error::INVALID_VALUE;
	#undef TRY_BUILD
}

std::unique_ptr<Value> Value::eval(const Operator op, const Value* const val2) const {
	// Unary operator:
	if (val2 == nullptr)
		return eval(op);
	// FIXME: Maybe do not use preprocessor to do this?? 
#define TRY_EVAL(T) 															  \
	try {																		  \
		const T* const val = dynamic_cast<const T* const>(val2);		          \
		return eval(op, val);													  \
	}																			  \
	catch (...) {}													  

	TRY_EVAL(Number);
	TRY_EVAL(Duration);

	throw Error::OPER_NOT_IMPL;
#undef TRY_EVAL
}
