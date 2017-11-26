#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/typeCalc.h"
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
			Value expect(textValue);
			Evaluator e;
			Assert::IsTrue(e.evaluate(textValue) == expect, L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple addition to test if the basic evaluation logic is working
		TEST_METHOD(SimpleEvaluationTest)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("2+2") == Value("4"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A test for operator's priority
		TEST_METHOD(OperatorPriorityTest)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("1+2*3") == Value("7"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A basic test for parentheses
		TEST_METHOD(ParenthesesTest)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("(1+2)*3") == Value("9"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Nested parentheses
		TEST_METHOD(NestedParenthesesTest)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("(5+(2*(3+3))+6)/2") == Value("11.5"), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Managing whitespaces
		TEST_METHOD(IgnoringWhitespacesTest)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("(5 + (2 * (3 + 3)) + 6) / 2") == Value("11.5"), L"evaluate did not return expected value.", LINE_INFO());
		}
	};
}