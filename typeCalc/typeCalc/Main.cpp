#include "Evaluator.h"

using namespace typeCalc;
int main(int, char*[])
{
	std::unique_ptr<Value> v1 = Evaluator::evaluate("-5 + 5");
	return 0;
}