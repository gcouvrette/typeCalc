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
		TEST_METHOD(EmptyFormulaReturnsNull)
		{
			Evaluator e;
			TEST_EXCEPTION(e.evaluate(""), typeCalc::EvalError, FORMULA_EMPTY);
		}

		// Calling evaluate with a simple value should return itself in a Value
		TEST_METHOD(SingleValueReturnsItself)
		{
			std::string textValue = "5";
			Value expect(textValue);
			Evaluator e;
			Assert::IsTrue(e.evaluate(textValue) == expect, L"evaluate did not return expected value.", LINE_INFO());
		}

		// Calling evaluate with a simple value should return itself in a Value
		TEST_METHOD(SimpleEvaluation)
		{
			Evaluator e;
			Assert::IsTrue(e.evaluate("2+2") == Value("4"), L"evaluate did not return expected value.", LINE_INFO());
		}
	};
}