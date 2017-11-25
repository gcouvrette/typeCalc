#include "typeCalc.h"

using namespace typeCalc;
Value Evaluator::evaluate(std::string formula)
{
	if (formula.empty())
		throw FORMULA_EMPTY;

	return Value(formula);
}
