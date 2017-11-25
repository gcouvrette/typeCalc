#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/typeCalc.h"

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
			try {
				typeCalc::EvaluateFormula("");
				Assert::Fail(L"EvaluateFormula did not fail.", LINE_INFO()); // Should never be reached if EvaluateFormula "Throws".
			}
			catch (typeCalc::EvalError e) {
				Assert::IsTrue(e == FORMULA_EMPTY, L"Wrong error type: Expected FORMULA_ERROR.", LINE_INFO());
			}
			catch (...) {
				Assert::Fail(L"Function did not throw the proper exception type.", LINE_INFO());
			}
		}

	};
}