#pragma once
#include "Operator.h"
#include "Value.h"
#include <string>
#include <memory>
#include <vector>
#include <stack>

namespace typeCalc {

	// This class is used to evaluate formulas.
	class Evaluator {
	public:
		// This function evaluates a formula and return the resulting value
		static std::unique_ptr<Value> evaluate(const std::string& formula);

	private:
		// Token can be either an Operator or a Value. Check bool "isValue" to know which one it is before using.
		struct Token {
			Token(Operator op);
			Token(std::unique_ptr<Value> Value);
			bool isValue;
			Operator asOperator;
			std::unique_ptr<Value> asValue;
		};

		// Transform a string in a list of tokens
		static std::vector<Token> tokenize(const std::string& formula);
		// Takes a string, add it to the token list as a new token Value and empties the string.
		static void completeValue(std::string& valueStr, std::vector<Token>& tokens);
		// Pop the topmost operator and applies it to the last 2 values stacked in the value stack.
		// unwrapping_par: Set to TRUE when unwrapping parentheses, it will THROW if the operator list is empty. 
		// It returns false when we pop a delimiter (Open parenthese or once we empty the stack)
		static bool pop(std::stack<std::unique_ptr<Value>>& values, std::stack<Operator>& operators, bool unwrapping_par = false);
	};
}