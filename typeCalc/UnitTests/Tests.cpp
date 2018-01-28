#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/value.h"
#include "../typeCalc/Number.h"
#include "../typeCalc/Duration.h"
#include "../typeCalc/Evaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace typeCalc;

namespace UnitTests
{
	TEST_CLASS(TypeCalcTests)
	{
	public:
		// Calling evaluate with an empty string should fail.
		TEST_METHOD(EmptyFormulaReturnsNullTest)
		{
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate(""); });
		}

		// Calling evaluate with a simple value should return itself in a Value
		TEST_METHOD(SingleValueReturnsItselfTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("5") == Number(5), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple addition to test if the basic evaluation logic is working
		TEST_METHOD(SimpleEvaluationTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("2+2") == Number(4), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A test for operator's priority
		TEST_METHOD(OperatorPriorityTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("1+2*3") == Number(7), L"evaluate did not return expected value.", LINE_INFO());
		}

		// A basic test for parentheses
		TEST_METHOD(ParenthesesTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("(1+2)*3") == Number(9), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Nested parentheses
		TEST_METHOD(NestedParenthesesTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("(5+(2*(3+3))+6)/2") == Number(11.5), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Managing whitespaces
		TEST_METHOD(IgnoringWhitespacesTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("(5 + (2 * (3 + 3)) + 6) / 2") == Number(11.5), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Misformed formula
		TEST_METHOD(MisformedFormulaTest)
		{
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate("("); });
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate("+"); });
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate("1++1"); });
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate(")"); });
			Assert::ExpectException<std::exception>([] { Evaluator::evaluate("((1+1)"); });
		}

		// Simple typed calculation(duration + duration)
		TEST_METHOD(DurationTypeTest)
		{
			Assert::IsTrue(*Evaluator::evaluate("1h30 + 1h30") == Duration(10800), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple typed calculation(duration * number)
		TEST_METHOD(DurationTimesNumber)
		{
			Assert::IsTrue(*Evaluator::evaluate("1h30 * 2") == Duration(10800), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Negative number
		TEST_METHOD(NegativeNumber)
		{
			Assert::IsTrue(*Evaluator::evaluate("-5 + 6") == Number(1), L"evaluate did not return expected value.", LINE_INFO());
		}
	};
}