#pragma once
#include <string>

namespace typeCalc {
	class Value {
	public:
		virtual std::string typeName() const;

		// Compares two values to see if both their quantities and types matches
		virtual bool operator==(const Value& val) const = 0;

		// These methods applies an operation to the this value, using the value specified in parameters.
		virtual void add(const Value& operand) = 0;
		virtual void sub(const Value& operand) = 0;
		virtual void mult(const Value& operand) = 0;
		virtual void div(const Value& operand) = 0;
	};
}
