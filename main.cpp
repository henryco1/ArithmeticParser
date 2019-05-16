#include <iostream>
#include <string>
#include "parser.h"
#include <assert.h>
/*
Henry Co Arithmetic Parser
This parser can handle the following:

1. addition
2. subtraction
3. multiplication
4. division
5. exponents
6. decimals
7. negative numbers
8. parentheses

The parser also checks against invalid inputs, such as letters, missing parentheses,
and division by zero. When the program starts the user is prompted to enter a
mathematical expression which will be calculated upon pressing enter. 
The program can only handle numbers <= DBL_MAX.
*/
void tests() {
	ArithmeticParser parser;

	assert(parser.parse("1") == 1);
	assert(parser.parse("2.3") == 2.3);
	assert(parser.parse("1+1.123") == 2.123);
	assert(parser.parse("1-1") == 0);
	assert(parser.parse("1*1") == 1);
	assert(parser.parse("1/1") == 1);
	assert(parser.parse("1^1") == 1);
	assert(parser.parse("4+-1") == 3);
	assert(parser.parse("(1^1)") == 1);
	assert(parser.parse("1*(23)") == 23);
	assert(parser.parse("2^-8") == 0.00390625);
	assert(parser.parse("2^(-8+8)") == 1);
	assert(parser.parse("2^1.1") == 2.1435469250725862622175554861314594745635986328125);
	// assert(std::isnan(parser.parse("2/0")) == true);

	assert(parser.parse("1^   1") == 1);
	assert(parser.parse("(      2+ 3  )") == 5);
	assert(parser.parse("2^ ( 4+  4) - 1") == 255);
	assert(parser.parse("2^ ( 2 * (2*2 )    ) - - 1") == 257);

	assert(parser.parse("(3+4)*6") == 42);
	assert(parser.parse("(4-2)*4") == 8);
	assert(parser.parse("(2/4)^4") == 0.0625);
	assert(parser.parse("(2*4)-4") == 4);
	assert(parser.parse("(2.5+2.5)/5") == 1);

	assert(parser.parse("(1^3*3-2/1)") == 1);
	assert(parser.parse("1+(2*(3)/1^(2+3))*1+0") == 7);
	assert(parser.parse("((1+3))") == 4);
	assert(parser.parse("2^(2^(-2)^(2))") == 65536);

	assert(parser.parse("500000+100000000") == 100500000);
	assert(parser.parse("123456789+                                123456789") == 246913578);
	assert(parser.parse("500000+100000000+0") == 100500000);
	assert(parser.parse("500000+100000000-100000000000") == -99899500000);
	assert(parser.parse("111111111111111111+999999999999999999") == 1111111111111111111);
	assert(parser.parse("1*999999999999999999") == 999999999999999999);
}
int main() {
	std::cout << "Henry Co Arithmetic Parser\n";
	tests();
	while (1) {
		ArithmeticParser parser;
		char input[310];
		std::cout << "What do you want to calculate?\n";
		std::cin.getline(input, sizeof(input));
		double out = parser.parse(input);
		std::cout << " = " << out << std::endl;
	}
	return 0;
}
