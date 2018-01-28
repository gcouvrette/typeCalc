#include "Evaluator.h"
#include "Duration.h"

using namespace typeCalc;
int main(int, char*[])
{
	std::unique_ptr<Value> v1 = Evaluator::evaluate("1.5 * 1h30");
	Duration d(2, 15, 00);
	return 0;
}