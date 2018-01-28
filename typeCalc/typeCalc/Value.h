#pragma once
#include <string>
#include <memory>

namespace typeCalc {
	class Value {
	public:
		virtual std::string typeName() const;

		// Compares two values to see if both their quantities and types matches
		virtual bool operator==(const Value& val) const = 0;

		// These methods applies an operation to the this value, using the value specified in parameters.
		virtual std::unique_ptr<Value> add(const Value& operand) const = 0;
		virtual std::unique_ptr<Value> sub(const Value& operand) const = 0;
		virtual std::unique_ptr<Value> mult(const Value& operand) const = 0;
		virtual std::unique_ptr<Value> div(const Value& operand) const = 0;
	};
}
