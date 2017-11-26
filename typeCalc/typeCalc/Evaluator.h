#pragma once
#include <string>
#include "Value.h"
#include "Operator.h"
#include <memory>
#include <vector>
#include <stack>

namespace typeCalc {
	// Error codes used by evaluate when parsing or evaluating:
	enum EvalError {
		FORMULA_EMPTY,
		UNEXPECTED_OP,
		UNEXPECTED_FORMULA_END,
		UNEXPECTED_END_PAR,
		MISSING_VALUE,
		MALFORMED_FORMULA,
		UNKNOWN_VALUE
	};

	// This class is used to evaluate formulas.
	class Evaluator {
	public:
		// This function evaluates a formula and return the resulting value
		Value evaluate(std::string formula);

	private:
		// Token can be either an Operator or a Value.
		class Token {
		public:
			Token(std::string);
			bool isVal() const;
			Value asValue() const;
			Operator asOperator() const;
		private:
			bool _isVal;
			Operator _op;
			std::unique_ptr<Value> _val;
		};

		// Transform a string in a list of tokens
		std::vector<Token> tokenize(std::string& formula) const;
		// Pop the topmost operator and applies it to the last 2 values stacked in the value stack.
		// unwrapping_par: Set to TRUE when unwrapping parentheses, it will THROW if the operator list is empty. 
		// It returns false when we pop a delimiter (Open parenthese or once we empty the stack)
		bool pop(std::stack<Value>& values, std::stack<Operator>& operators, bool unwrapping_par = false);
	};
}