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
			TEST_EXCEPTION(Value(""), Value::Error, Value::EMPTY_TEXT);
		}
		
		TEST_METHOD(ConstructorForIntFromString)
		{
			Value test("10");
			Assert::IsTrue(test.qty() == 10.0, L"Incorrect quantity.");
			Assert::IsTrue(test.type() == Value::Type::NUMBER, L"Incorrect data type.");
		}

		TEST_METHOD(ConstructorForDecimalFromString)
		{
			Value test("10241.1225");
			Assert::IsTrue(test.qty() == 10241.1225, L"Incorrect quantity.");
			Assert::IsTrue(test.type() == Value::Type::NUMBER, L"Incorrect data type.");
		}
	};
}