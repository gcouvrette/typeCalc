#pragma once
#include <string>

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
			MULTIPLE_DECIMAL_POINTS
		};
		// Parses the string to construct the Value. May throw "Value::Error" if parsing fails
		Value(std::string text);
		// Compares two values to see if both their quantity and type matches
		bool operator==(const Value & val) const;
		// Returns the "raw" quantity of this value
		double qty() const;
		// Returns the type of this value
		Type type() const;
	private:
		double _qty;
	};

	/* This function parses and evaluates the formula from the string 
	   passed in parameters .*/
	Value EvaluateFormula(std::string formula);

	// Error codes used by EvaluateFormula when parsing or evaluating:
	enum EvalError {
		FORMULA_EMPTY,

	};
};
