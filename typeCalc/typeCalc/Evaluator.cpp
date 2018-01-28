#include "Evaluator.h"
#include "Value.h"
#include "Number.h"
#include "Duration.h"
#include <stack>
#include <regex>
#include <memory>

using namespace typeCalc;
std::unique_ptr<Value> Evaluator::evaluate(const std::string& formula) {
	if (formula.empty())
		throw std::exception("Nothing to evaluate.");

	// Step 1: tokenize the string:
	auto tokens = tokenize(formula);

	std::stack<std::unique_ptr<Value>> values; // Holds values as they are being processed.
	std::stack<Operator> operators; // Hold operators in priority order.

	// Evaluation logic:
	for (Token& token : tokens) {
		// If the token a value, add it to the value stack:
		if (token.isValue)
			values.push(std::move(token.asValue));
		else {
			Operator op = token.asOperator;
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

	if (values.size() != 1)
		throw std::exception("Malformed formula.");
	return std::move(values.top());
}

// This function splits and cleans the input formula in potential values and operators.
std::vector<Evaluator::Token> Evaluator::tokenize(const std::string& formula) {
	std::vector<Evaluator::Token> tokens;

	std::string valueStr;
	// Iterate on each character in the formula:
	for (char c : formula) {
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n') // skip all space/tab/newline
			continue;
		// Process simple operators:
		switch (c) {
		case '(':
			completeValue(valueStr, tokens);
			tokens.emplace_back(Operator::OPEN_P);
			break;
		case ')':
			completeValue(valueStr, tokens);
			tokens.emplace_back(Operator::CLOSING_P);
			break;
		case '+':
			completeValue(valueStr, tokens);
			tokens.emplace_back(Operator::PLUS);
			break;
		case '*':
			completeValue(valueStr, tokens);
			tokens.emplace_back(Operator::MULT);
			break;
		case '/':
			completeValue(valueStr, tokens);
			tokens.emplace_back(Operator::DIV);
			break;
		case '-': // Negative symbol is an exception because it is used both for negative values and as an operator.
			if (!valueStr.empty()) { // If we are parsing a value, stop parsing and add a subtraction to the tokens:
				completeValue(valueStr, tokens);
				tokens.emplace_back(Operator::MINUS);
				break;
			} // else, consider as part of the value (default case)
		default:
			valueStr += c;
		}
	}

	// Finally, if there is still a value remaining, process it:
	completeValue(valueStr, tokens);
	return std::move(tokens);
}

void Evaluator::completeValue(std::string& valueStr, std::vector<Token>& tokens) {
	if (valueStr.empty())
		return;

	// Try matching for numbers:
	if (std::regex_match(valueStr, std::regex("(-){0,1}\\d*(\\.\\d+){0,1}"))) {
		tokens.emplace_back(std::unique_ptr<Value>(new Number(stof(valueStr))));
	}
	// Try matching with a duration: (format is 00h00m00s, where the last symbol may be omitted (ex: 1h22 == 1h22m, 22m30s == 22m30, 1h00 == 1h)
	else if (std::regex_match(valueStr, std::regex("(-){0,1}(?=(\\d+h{0,1}){0,1}(\\d+m{0,1}){0,1}(\\d+s{0,1}){0,1})(.*(h|m|s).*)"))) {
		std::string number;
		int seconds = 0;
		int nextUnitFactor = 0;
		for (char c : valueStr) {
			if (c >= '0' && c <= '9')
				number += c;
			else if (c == 'h') {
				seconds += (3600 * stoi(number));
				number = "";
				nextUnitFactor = 60;
			}
			else if (c == 'm') {
				seconds += (60 * stoi(number));
				number = "";
				nextUnitFactor = 1;
			}
			else if (c == 's') {
				seconds += (stoi(number));
				number = "";
			}
		}
		if (!number.empty())
			seconds += (stoi(number) * nextUnitFactor);
		tokens.emplace_back(std::unique_ptr<Value>(new Duration(0, 0, seconds, (valueStr[0] == '-') /* Is Negative? */)));
	}
	// Unknown value, thow error message.
	else {
		throw std::exception(("Cannot parse value: " + valueStr).c_str());
	}
	// The value string was consumed, clear it.
	valueStr.clear();
}


bool typeCalc::Evaluator::pop(std::stack<std::unique_ptr<Value>>& values, std::stack<Operator>& operators, bool unwrapping_par /* = false */) {
	if (operators.empty())
		if (unwrapping_par) // We have nothing left to process and should throw (while unwrapping parentheses).
			throw std::exception("Unbalanced parentheses.");
		else
			return false; // We emptied the stack. Stop.

	// Get the top operator:
	const Operator op = operators.top();
	operators.pop();

	// We popped an open parenthese. If unwrapping_par, Stop.
	if (op == OPEN_P)
		if (unwrapping_par)
			return (false);
		else
			throw std::exception("Unbalanced parentheses.");
	// Extract the last 2 values of the stack:
	if (values.empty())
		throw std::exception("Missing value for operation.");
	std::unique_ptr<Value> val2 = std::move(values.top());
	values.pop();
	if (values.empty())
		throw std::exception("Missing value for operation.");
	std::unique_ptr<Value> val = std::move(values.top());
	values.pop();
	// Process them
	switch (op) {
	case Operator::PLUS:
		val = val->add(*val2.get());
		break;
	case Operator::MINUS:
		val = val->sub(*val2.get());
		break;
	case Operator::MULT:
		val = val->mult(*val2.get());
		break;
	case Operator::DIV:
		val = val->div(*val2.get());
		break;
	}
	// Push it back on the stack for the next pop:
	values.push(std::move(val));
	return true;
}

Evaluator::Token::Token(Operator op) {
	asOperator = op;
	isValue = false;
}

Evaluator::Token::Token(std::unique_ptr<Value> Value) {
	asValue = std::move(Value);
	isValue = true;
}
