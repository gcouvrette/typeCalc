#pragma once
#include "Value.h"

namespace typeCalc {
	/* This class is a value that holds a number. */
	class Number : public Value {
	public:
		Number(double qty);
		double qty() const;

		virtual bool operator==(const Value& val) const override;
		// These methods applies an operation to the this value, using the value specified in parameters.
		virtual std::unique_ptr<Value> add(const Value& operand) const override;
		virtual std::unique_ptr<Value> sub(const Value& operand) const override;
		virtual std::unique_ptr<Value> mult(const Value& operand) const override;
		virtual std::unique_ptr<Value> div(const Value& operand) const override;
	private:
		double _qty;
	};
}
