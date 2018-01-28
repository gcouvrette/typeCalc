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
			Assert::IsTrue(*Evaluator::evaluate("1h30 + 1h30m00") == Duration(3, 00, 00), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("1h30 + 1h30m00s") == Duration(3, 00, 00), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("1h30m + 1h + 30m") == Duration(3, 00, 00), L"evaluate did not return expected value.", LINE_INFO());
		}

		// Simple typed calculation(duration * number)
		TEST_METHOD(DurationTimesNumber)
		{
			Assert::IsTrue(*Evaluator::evaluate("1h30 * 2") == Duration(3, 00, 00), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("1.5 * 1h30") == Duration(2, 15, 00), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("(1h30 * 3 + 2h01) / 2") == Duration(3, 15, 30), L"evaluate did not return expected value.", LINE_INFO());
		}

		TEST_METHOD(NegativeNumber)
		{
			Assert::IsTrue(*Evaluator::evaluate("-5 + 6") == Number(1), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("-5 + -6") == Number(-11), L"evaluate did not return expected value.", LINE_INFO());
		}

		TEST_METHOD(NegativeDuration)
		{
			Assert::IsTrue(*Evaluator::evaluate("-5h22 + -6h11") == Duration(11, 33, 00, true), L"evaluate did not return expected value.", LINE_INFO());
			Assert::IsTrue(*Evaluator::evaluate("-5h22 + 6h11") == Duration(0, 49, 00), L"evaluate did not return expected value.", LINE_INFO());
		}

		TEST_METHOD(ValueFormatting)
		{
			Assert::IsTrue(Duration(1,30,00).asString().compare("1h30m"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Duration(1, 30, 00, true).asString().compare("-1h30m"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Number(10).asString().compare("10"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Number(-8).asString().compare("-8"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Number(0).asString().compare("0"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Duration(0).asString().compare("0s"), L"Format did not return expected string.", LINE_INFO());
			Assert::IsTrue(Number(0.255).asString().compare("0.255"), L"Format did not return expected string.", LINE_INFO());
		}
	};
}