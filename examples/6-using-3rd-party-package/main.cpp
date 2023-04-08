#include <iostream>

#include "my_math/addition.h"
#include "my_math/division.h"

int main()
{
	float first_no, second_no, result_add, result_div;

	std::cout<< "Enter first number\t";
	std::cin>> first_no;
	std::cout<< "Enter second number\t";
	std::cin>> second_no;

	result_add = addition(first_no , second_no);
	result_div = division(first_no , second_no);

	std::cout << "Addition: " << result_add << '\n';
	std::cout << "Division: " << result_div << '\n';

	return 0;
}
