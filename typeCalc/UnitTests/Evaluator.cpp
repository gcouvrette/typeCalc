#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/value.h"
#include "../typeCalc/Evaluator.h"
#include "Defines.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace typeCalc;

namespace UnitTests
{
	// Tests for class Evaluator
	TEST_CLASS(EvaluatorTests)
	{
	public:
		// Calling evaluate with an empty string should return an EmptyFormula error.
		TEST_METHOD(EmptyFormulaReturnsNullTest)
		{
			Evaluator e;
			TEST_EXCEPTION(e.evaluate(""), typeCalc::EvalError, FORMULA_EMPTY);
		}

		// Calling evaluate with a simple value should return itself in a Value
		TEST_METHOD(SingleValueReturnsItselfTest)
		{
			std::string textValue = "5";
			std::unique_ptr<Value> expect = Value::fromString(textValue);
			Evaluator e;
			Assert::IsTrue(*e.evaluate(textValue) == (*expect), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple addition to test if the basic evaluation logic is working
		TEST_METHOD(SimpleEvaluationTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("2+2") == *Value::fromString("4"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A test for operator's priority
		TEST_METHOD(OperatorPriorityTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("1+2*3") == *Value::fromString("7"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A basic test for parentheses
		TEST_METHOD(ParenthesesTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("(1+2)*3") == *Value::fromString("9"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Nested parentheses
		TEST_METHOD(NestedParenthesesTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("(5+(2*(3+3))+6)/2") == *Value::fromString("11.5"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Managing whitespaces
		TEST_METHOD(IgnoringWhitespacesTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("(5 + (2 * (3 + 3)) + 6) / 2") == *Value::fromString("11.5"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Misformed formula
		TEST_METHOD(MisformedFormulaTest)
		{
			Evaluator e;
			TEST_EXCEPTION(e.evaluate("("), typeCalc::EvalError, typeCalc::EvalError::MALFORMED_FORMULA);
			TEST_EXCEPTION(e.evaluate("+"), typeCalc::EvalError, typeCalc::EvalError::MISSING_VALUE);
			TEST_EXCEPTION(e.evaluate("1++1"), typeCalc::EvalError, typeCalc::EvalError::MISSING_VALUE);
			TEST_EXCEPTION(e.evaluate(")"), typeCalc::EvalError, typeCalc::EvalError::UNEXPECTED_END_PAR);
			TEST_EXCEPTION(e.evaluate("((1+1)"), typeCalc::EvalError, typeCalc::EvalError::MALFORMED_FORMULA);
		}

		// Simple typed calculation(duration + duration)
		TEST_METHOD(DurationTypeTest)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("1h30 + 1h30") == *Value::fromString("3h00"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple typed calculation(duration * number)
		TEST_METHOD(DurationTimesNumber)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("1h30 * 2") == *Value::fromString("3h00"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Negative number
		TEST_METHOD(NegativeNumber)
		{
			Evaluator e;
			Assert::IsTrue(*e.evaluate("-5 + 6") == *Value::fromString("1"), L"evaluate did not return expected value.", LINE_INFO());
		}
	};
}