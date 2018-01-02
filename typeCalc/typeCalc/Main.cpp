#include "Evaluator.h"

using namespace typeCalc;
int main(int, char*[])
{
	Evaluator e;
	std::unique_ptr<Value> v1 = e.evaluate("1h30 + 1h30");
	return 0;
}