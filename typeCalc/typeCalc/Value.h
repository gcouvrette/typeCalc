#pragma once
#include <string>
#include "Evaluator.h"
#include "Operator.h"

namespace typeCalc {
	/* This class represents a Value, along with it's data type. */
	class Value {
	public:
		enum Type {
			NUMBER,
			DURATION,
			TIME,
			DISTANCE
		};

		// Errors used when parsing Values from a String.
		enum Error {
			EMPTY_TEXT,
			MULTIPLE_DECIMAL_POINTS,
			OPER_NOT_IMPL
		};
		// Parses the string to construct the Value. May throw "Value::Error" if parsing fails
		Value(std::string text);
		// Constructor directly from qty
		Value(double qty);
		// Copy constructor
		Value(const Value& value);
		// Compares two values to see if both their quantity and type matches
		bool operator==(const Value & val) const;
		// Returns the "raw" quantity of this value
		double qty() const;
		// Returns the type of this value
		Type type() const;

		Value eval(Operator op, Value val2) const;
	private:
		double _qty;
	};
}