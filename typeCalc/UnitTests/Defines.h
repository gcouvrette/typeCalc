#pragma once

#define TEST_EXCEPTION(code_to_test, expected_exception_type, expected_exception_value) \
try {																														  \
code_to_test;																								                  \
Assert::Fail(L"code_to_test did not fail.", LINE_INFO()); /* Should never be reached if code_to_test "Throws".	*/            \
}																															  \
catch (expected_exception_type e) {																							  \
	Assert::IsTrue(e == expected_exception_value, L"Wrong value of the correct exception type was returned.", LINE_INFO());	  \
}																															  \
catch (...) {																												  \
	Assert::Fail(L"Function did not throw the proper exception type.", LINE_INFO());                                          \
}																															  \
  