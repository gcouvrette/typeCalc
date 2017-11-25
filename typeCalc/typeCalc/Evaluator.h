#pragma once
#include <string>
#include "Value.h"

namespace typeCalc {
	// Error codes used by evaluate when parsing or evaluating:
	enum EvalError {
		FORMULA_EMPTY,

	};

	// This class is used to evaluate formulas.
	class Evaluator {
	public:
		// This function evaluates a formula and return the resulting value
		Value evaluate(std::string formula);
	};
}