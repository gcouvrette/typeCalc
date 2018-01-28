#include "Evaluator.h"
#include "Duration.h"
#include <iostream>

using namespace typeCalc;
int main(int argc, char* argv[])
{
	try {
		std::string formula;
		for (int i = 1; i < argc; i++)
			formula += argv[i];
		std::unique_ptr<Value> answer = Evaluator::evaluate(formula);
		std::cout << answer->asString() << std::endl;
	} catch(std::exception ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	return 0;
}