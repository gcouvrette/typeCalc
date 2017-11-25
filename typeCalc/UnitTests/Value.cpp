#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/typeCalc.h"
#include "Defines.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace typeCalc;

namespace UnitTests
{
	// Tests for class "typeCalc::Value"
	TEST_CLASS(ValueTests)
	{
	public:
		// Constructing a Value with an empty string should fail.
		TEST_METHOD(EmptyStringShouldFail)
		{
			TEST_EXCEPTION(Value(""), Value::Error, Value::Error::EMPTY_TEXT);
		}
		
		TEST_METHOD(ConstructorForIntFromString)
		{
			Value test("10");
			Assert::IsTrue(test.qty() == 10.0, L"Incorrect quantity.");
			Assert::IsTrue(test.type() == Value::Type::NUMBER, L"Incorrect data type.");
			// Test negative values:
			Value testNeg("-10");
			Assert::IsTrue(testNeg.qty() == -10.0, L"Negative numbers not working.");
		}

		TEST_METHOD(CannotHaveMultiDecimals)
		{
			TEST_EXCEPTION(Value("10.5.5"), Value::Error, Value::Error::MULTIPLE_DECIMAL_POINTS);
		}

		TEST_METHOD(ConstructorForDecimalFromString)
		{
			Value test("10241.1225");
			Assert::IsTrue(test.qty() == 10241.1225, L"Incorrect quantity.");
			Assert::IsTrue(test.type() == Value::Type::NUMBER, L"Incorrect data type.");
		}

		TEST_METHOD(EqualityOperator)
		{
			Value v1("1234"), v2("1234"), v3("5");
			Assert::IsTrue(v1 == v2, L"Equality operator did not detect actual equality.");
			Assert::IsFalse(v1 == v3, L"Equality operator incorrectly detected an equality.");
		}
	};
}