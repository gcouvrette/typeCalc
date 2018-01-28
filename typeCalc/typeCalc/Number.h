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
		virtual void add(const Value& operand) override;
		virtual void sub(const Value& operand) override;
		virtual void mult(const Value& operand) override;
		virtual void div(const Value& operand) override;
	private:
		double _qty;
	};
}
