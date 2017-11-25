#pragma once
#include <string>

namespace typeCalc {
	enum EvalError {
		FORMULA_EMPTY,

	};

	class Value {

	};
	/* This function parses and evaluates the formula from the string 
	   passed in parameters .*/
	Value EvaluateFormula(std::string formula);
};
