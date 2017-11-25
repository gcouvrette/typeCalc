#include "stdafx.h"
#include "CppUnitTest.h"
#include "../typeCalc/CharHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	// Tests for defines in "CharHelpers"
	TEST_CLASS(CharHelpersTests)
	{
	public:
		// Testing macro: IS_DIGIT
		TEST_METHOD(IS_DIGIT_TEST)
		{

			Assert::IsTrue(IS_DIGIT('0'), L"0 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('1'), L"1 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('2'), L"2 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('3'), L"3 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('4'), L"4 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('5'), L"5 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('6'), L"6 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('7'), L"7 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('8'), L"8 not recognized as a digit!");
			Assert::IsTrue(IS_DIGIT('9'), L"9 not recognized as a digit!");
			Assert::IsFalse(IS_DIGIT(' '), L"Whitespace recognized as a string.");
			Assert::IsFalse(IS_DIGIT('.'), L"Dot recognized as a string.");
			Assert::IsFalse(IS_DIGIT('a'), L"a recognized as a string.");
			Assert::IsFalse(IS_DIGIT('Z'), L"Z recognized as a string.");
			Assert::IsFalse(IS_DIGIT('!'), L"! recognized as a string.");
		}
		// Testing macro: TO_INT
		TEST_METHOD(TO_INT_TEST)
		{
			Assert::IsTrue(TO_INT('0') == 0, L"0 incorrectly converted!");
			Assert::IsTrue(TO_INT('1') == 1, L"1 incorrectly converted!");
			Assert::IsTrue(TO_INT('2') == 2, L"2 incorrectly converted!");
			Assert::IsTrue(TO_INT('3') == 3, L"3 incorrectly converted!");
			Assert::IsTrue(TO_INT('4') == 4, L"4 incorrectly converted!");
			Assert::IsTrue(TO_INT('5') == 5, L"5 incorrectly converted!");
			Assert::IsTrue(TO_INT('6') == 6, L"6 incorrectly converted!");
			Assert::IsTrue(TO_INT('7') == 7, L"7 incorrectly converted!");
			Assert::IsTrue(TO_INT('8') == 8, L"8 incorrectly converted!");
			Assert::IsTrue(TO_INT('9') == 9, L"9 incorrectly converted!");
		}
	};
}