#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/typeCalc.h"
#include "Defines.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace typeCalc;

namespace UnitTests
{
	// Tests for function "typeCalc::EvaluateFormula()"
	TEST_CLASS(EvaluateFormulaTests)
	{
	public:
		// Calling EvaluateFormula with an empty string should return an EmptyFormula error.
		TEST_METHOD(EmptyFormulaReturnsNull)
		{
			Evaluator e;
			TEST_EXCEPTION(e.evaluate(""), typeCalc::EvalError, FORMULA_EMPTY);
		}

		// Calling EvaluateFormula with a simple value should return itself in a Value
		TEST_METHOD(SingleValueReturnsItself)
		{
			std::string textValue = "5";
			typeCalc::Value expect(textValue);
			Evaluator e;
			Assert::IsTrue(e.evaluate(textValue) == expect, L"EvaluateFormula did not return expected value.", LINE_INFO());
		}

	};
}