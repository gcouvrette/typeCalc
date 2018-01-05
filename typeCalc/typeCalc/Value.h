#pragma once
#include <string>
#include "Operator.h"
#include <memory>

namespace typeCalc {
	class Number;
	class Duration;

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
			OPER_NOT_IMPL,
			INVALID_VALUE
		};
		// Constructs a value from the string in parameter of the right type.
		static std::unique_ptr<Value> fromString(const std::string& text);
		// Compares two values to see if both their quantity and type matches
		virtual bool operator==(const Value& val) const = 0;
		// This function will be called to evaluate an operation with a specific value in second val (Second value may be null for unary operations)
		// It will then dispatch to the corresponding call using a more precise value type. Only the latter needs to be implemented by each Value type.
		std::unique_ptr<Value> eval(const Operator op, const Value* const val2) const;
	protected:
		// Unary operation
		virtual std::unique_ptr<Value> eval(const Operator op) const = 0;
		// Operation with a Duration
		virtual std::unique_ptr<Value> eval(const Operator op, const Duration* const val2) const = 0;
		// Operation with a Number
		virtual std::unique_ptr<Value> eval(const Operator op, const Number* const val2) const = 0;

	};

	/* This class is a value that holds a number. */
	class Number : public Value {
	public:
		/* Parses the string and initialize a Number value if possible.
		May throw an Exception if a parsing error occurs. */
		Number(const std::string& text);
		// Initialize directly with the number in parameter.
		Number(double qty);

		/* From: typeCalc::Value */
		virtual bool operator==(const Value& val) const;
		double qty() const;
	protected:
		// Unary operation
		virtual std::unique_ptr<Value> eval(const Operator op) const;
		// Operation with a Duration
		virtual std::unique_ptr<Value> eval(const Operator op, const Duration* const val2) const;
		// Operation with a Number
		virtual std::unique_ptr<Value> eval(const Operator op, const Number* const val2) const;
	private:
		double _qty;
	};

	/* This class is a value that holds durations. */
	class Duration : public Value {
	public:
		/* Parses the string and initialize a Duration value if possible.
		   May throw an Exception if a parsing error occurs. */
		Duration(const std::string& text);
		Duration(int seconds);

		/* From: typeCalc::Value */
		virtual bool operator==(const Value& val) const;
		virtual double qty() const;
	protected:
		// Unary operation
		virtual std::unique_ptr<Value> eval(const Operator op) const;
		// Operation with a Duration
		virtual std::unique_ptr<Value> eval(const Operator op, const Duration* const val2) const;
		// Operation with a Number
		virtual std::unique_ptr<Value> eval(const Operator op, const Number* const val2) const;
	private:
		double _qty;
	};
}