#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/Value.h"
#include "Defines.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace typeCalc;

namespace UnitTests
{
	// Tests for "typeCalc::Value::fromString()" - The static function parsing and creating the corresponding Value object.
	TEST_CLASS(FromStringTests)
	{
	public:
		// Constructing a Value with an empty string should fail.
		TEST_METHOD(EmptyStringShouldFail)
		{
			TEST_EXCEPTION(Value::fromString(""), Value::Error, Value::Error::EMPTY_TEXT);
		}
		
		TEST_METHOD(ConstructorForIntFromString)
		{
			std::unique_ptr<Value> raw_value = Value::fromString("10");
			Number* test = dynamic_cast<Number*>(raw_value.get());			
			Assert::IsTrue(test->qty() == 10.0, L"Incorrect quantity.");
			// Test negative values:
			raw_value = Value::fromString("-10");
			Number* testNeg = dynamic_cast<Number*>(raw_value.get());
			Assert::IsTrue(testNeg->qty() == -10.0, L"Negative numbers not working.");
		}

		TEST_METHOD(CannotHaveMultiDecimals)
		{
			// No value type supports this stucture.
			TEST_EXCEPTION(Value::fromString("10.5.5"), Value::Error, Value::Error::INVALID_VALUE);
		}

		TEST_METHOD(ConstructorForDecimalFromString)
		{
			std::unique_ptr<Value> raw_value = Value::fromString("10241.1225");
			Number* test = dynamic_cast<Number*>(raw_value.get());
			Assert::IsTrue(test->qty() == 10241.1225, L"Incorrect quantity.");
		}

		TEST_METHOD(EqualityOperator)
		{
			std::unique_ptr<Value> v1 = Value::fromString("1234");
			std::unique_ptr<Value> v2 = Value::fromString("1234");
			std::unique_ptr<Value> v3 = Value::fromString("5");
			Assert::IsTrue(*v1 == *v2, L"Equality operator did not detect actual equality.");
			Assert::IsFalse(*v1 == *v3, L"Equality operator incorrectly detected an equality.");
		}
	};
	// Extra tests for value (ex: == operator)
	TEST_CLASS(MiscValueTests)
	{
		TEST_METHOD(EqualityOperator)
		{
			std::unique_ptr<Value> v1 = Value::fromString("1234");
			std::unique_ptr<Value> v2 = Value::fromString("1234");
			std::unique_ptr<Value> v3 = Value::fromString("5");
			Assert::IsTrue(*v1 == *v2, L"Equality operator did not detect actual equality.");
			Assert::IsFalse(*v1 == *v3, L"Equality operator incorrectly detected an equality.");
		}
	};
}