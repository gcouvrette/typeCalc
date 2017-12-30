#include "Evaluator.h"

using namespace typeCalc;
int main(int, char*[])
{
	Evaluator e;
	std::unique_ptr<Value> v1 = e.evaluate("2+2");
	std::unique_ptr<Value> v2 = Value::fromString("4");
	return 0;
}