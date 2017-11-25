#include "typeCalc.h"

using namespace typeCalc;
Value typeCalc::EvaluateFormula(std::string formula)
{
	if (formula.empty())
		throw FORMULA_EMPTY;

	return Value();
}
