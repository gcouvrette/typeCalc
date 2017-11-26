#include "typeCalc.h"
#include "CharHelpers.h"
#include <stack>

using namespace typeCalc;
Value Evaluator::evaluate(std::string formula) {
	if (formula.empty())
		throw FORMULA_EMPTY;

	// Step 1: tokenize the string:
	auto tokens = tokenize(formula);

	std::stack<Value> values; // Holds values as they are being processed.
	std::stack<Operator> operators; // Hold operators in priority order.

	// Evaluation logic:
	for (const Token& token : tokens) {
		// If the token a value, add it to the value stack:
		if (token.isVal())
			values.push(token.asValue());
		else {
			Operator op = token.asOperator();
			switch (op)
			{
				// If the operator is an open parentheses, simply push it no matter what:
			case OPEN_P:
				operators.push(op);
				break;
				// if the operator is a closing parentheses, we pop back each operator until the matching parenthese is found:
			case CLOSING_P:
				while (pop(values, operators, true)); // Pop until we get either an opened parentheses or we empty the stack.
				break;

			case MULT:
			case DIV:
			{
				// If we have already a symbol on the stack, check what the next operator is:
				if (!operators.empty()) {
					Operator topOp = operators.top();
					if (topOp == DIV || topOp == MULT) // If there is already a mult or div, pop it first:
						pop(values, operators);

				}
				// Then, push it to the stack.
				operators.push(op);
			}
			break;
			case PLUS:
			case MINUS:
			{
				// No matter what, we need to pop the last operator if there is one, except if it is a parenthesis:
				if (!operators.empty() && operators.top() != OPEN_P)
					pop(values, operators);
				// Then, push it to the stack.
				operators.push(op);
			}
			break;
			}
		}
	}

	// Once the tokens are all parsed, empty the remaining operators:
	while (pop(values, operators));

	return Value(values.top());
}

// This function splits and cleans the input formula in potential values and operators.
std::vector<Evaluator::Token> Evaluator::tokenize(std::string& formula) const {
	std::vector<Token> tokens;
	std::string currentString;
	for (const char& c : formula) {
		// Ignore whitespaces
		if (IS_WHITESPACE(c))
			continue;
		if (IS_OP(c)) {
			if (!currentString.empty())
				tokens.emplace_back(Token(currentString)); // Tokenize the last string
			currentString = "";
			currentString.push_back(c);
			tokens.emplace_back(Token(currentString)); // Push this operator right after
			currentString = "";
		}
		else
		{
			currentString.push_back(c); // This is part of a value, append to the current string
		}
	}
	// Once we reach the last symbol, we have to close the last token if we have one left:
	if (!currentString.empty())
		tokens.emplace_back(Token(currentString)); // Tokenize the last string

	return tokens;
}

bool typeCalc::Evaluator::pop(std::stack<Value>& values, std::stack<Operator>& operators, bool unwrapping_par /* = false */)
{
	if (operators.empty())
		if (unwrapping_par) // We have nothing left to process and should throw (while unwrapping parentheses).
			throw UNEXPECTED_END_PAR;
		else
			return false; // We emptied the stack. Stop.

	// Get the top operator:
	const Operator op = operators.top();
	operators.pop();

	// We popped an open parenthese. If unwrapping_par, Stop.
	if (op == OPEN_P)
		return (!unwrapping_par);
	// Extract the last 2 values of the stack:
	if (values.empty())
		throw MISSING_VALUE;
	Value val2 = values.top();
	values.pop();
	if (values.empty())
		throw MISSING_VALUE;
	Value val1 = values.top();
	values.pop();
	// Process them
	Value result = val1.eval(op, val2);
	// Push it back on the stack for the next pop:
	values.push(result);
	return true;
}


Evaluator::Token::Token(std::string str) : _isVal(false) {
	if (str == "+")
		_op = Operator::PLUS;
	else if (str == "-")
		_op = Operator::MINUS;
	else if (str == "*")
		_op = Operator::MULT;
	else if (str == "/")
		_op = Operator::DIV;
	else if (str == "(")
		_op = Operator::OPEN_P;
	else if (str == ")")
		_op = Operator::CLOSING_P;
	else
	{
		_val = std::unique_ptr<Value>(new Value(str));
		_isVal = true;
	}
}

bool Evaluator::Token::isVal() const {
	return _isVal;
}

Value Evaluator::Token::asValue() const {
	if (!isVal())
		throw std::exception("Operator token read as a value!");
	return Value(*_val); // Take a copy of the value in this 
}

Operator Evaluator::Token::asOperator() const {
	if (isVal())
		throw std::exception("Value token read as an operator!");
	return _op;
}