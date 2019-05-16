#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include "parser.h"
/*
This file contains the implementation of the arithmetic parser class
*/
double ArithmeticParser::parse(std::string input) {
	std::deque<Token> tokens = tokenize(input);
	try {	
		double out = parse_expr(tokens);
		if (tokens.front().get_value() != "end") 
			throw "Error: invalid input, bad number or operation\n";
		else if (std::isnan(out) || std::isinf(out))
			throw "Error: cannot divide by 0\n";
		else 
			return out;
	}
	catch (const char* msg) {
		std::cerr << msg;
		return NAN;
	}
}
bool ArithmeticParser::is_char_digit(char terminal) {
	char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
	for (int i=0; i<11; i++) {
		if (terminal == numbers[i]) 
			return true;
	}
	return false;
}
std::deque<Token> ArithmeticParser::tokenize(std::string input) {
	std::deque<Token> tokenList;
	for (int i=0; i<input.size(); i++) {
		if (!is_char_digit(input[i])) {
			if (input[i] == ' ') continue;
			std::string operatorStr;
			operatorStr.push_back(input[i]);
			tokenList.push_back(Token(operatorStr));
		} else {
			std::vector<char> tokBuffer;
			while (is_char_digit(input[i])) {
				tokBuffer.push_back(input[i]);
				i++;
			}
			i--;
			std::string number;
			for (int j=0; j<tokBuffer.size(); j++) 
				number.push_back(tokBuffer[j]);
			tokenList.push_back(Token(number));
		}
	}
	tokenList.push_back(Token("end"));
	return tokenList;
}
double ArithmeticParser::parse_expr(std::deque<Token> &tokInput) {
	double out;
	out = parse_term(tokInput);
	Token term1 = tokInput.front();
	while (term1.is_terminal("+") || term1.is_terminal("-")) {
		tokInput.pop_front();
		double term2 = parse_term(tokInput);
		if (term1.is_terminal("+"))
			out += term2;
		else 
			out -= term2;
		term1 = tokInput.front();
	}
	return out;
}
double ArithmeticParser::parse_term(std::deque<Token> &tokInput) {
	double out;
	out = parse_factor(tokInput);
	Token factor1 = tokInput.front();
	while (factor1.is_terminal("*") || factor1.is_terminal("/")) {
		tokInput.pop_front();
		double factor2 = parse_factor(tokInput);
		if (factor1.is_terminal("*"))
			out *= factor2;
		else if (factor1.is_terminal("/")) 
			out /= factor2;
		factor1 = tokInput.front();
	}
	return out;
}
double ArithmeticParser::parse_factor(std::deque<Token> &tokInput) {
	double out;
	int sign = 1;
	Token temp = tokInput.front();
	if (temp.is_terminal("-")) 
		sign = -1;
	if (sign < 0) 
		tokInput.pop_front(); 
	out = parse_item(tokInput);
	temp = tokInput.front();
	while (temp.is_terminal("^")) {
		tokInput.pop_front();
		double factor1 = parse_factor(tokInput);
		out = pow(out, factor1);
		temp = tokInput.front();
	}
	return out * sign;
}
double ArithmeticParser::parse_item(std::deque<Token> &tokInput) {
	double expr;
	Token item = tokInput.front();
	tokInput.pop_front(); 
	bool isNumber = true;
	for (char c: item.get_value()) 
		if (!is_char_digit(c)) isNumber = false;
	if (item.is_terminal("+") == true) 
		throw "Error: cannot have + before number\n";
	if (isNumber) 
		return item.get_double();
	if (item.is_terminal("(") != true) 
		throw "Error: received a bad number or bad ( input\n";
	expr = parse_expr(tokInput);
	if (tokInput.front().is_terminal(")") != true) 
		throw "Error: program needs an operator or ) input\n";
	tokInput.pop_front();
	return expr;
}