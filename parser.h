#include <string>
#include <deque>
#include "token.h"

class ArithmeticParser {
	/*
	This parser is a recursive descent parser that takes an input string 
	representing an arithmetic expression. This process involves three 
	major steps:
	
	1. Convert the input into smaller pieces called tokens
	2. Parse the input tokens. Involves error checking and recursively parsing
		the tokens following the structure of the context-free grammar
	3. Take the parsed tokens and compute their value.
	
	The CFG of the parser is as follows:
	expr -> term add-op term
	term -> factor mult-op factor 
	factor -> func-op item func-op factor
	item -> (expr) | number
	add-op -> + | -
	mult-op -> * | / 
	func-op -> - | ^
	number -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | . 
	*/
	public:
		double parse(std::string input);
	private:
		bool is_char_digit(char terminal);
		std::deque<Token> tokenize(std::string input);
		double parse_expr(std::deque<Token> &tokInput);
		double parse_term(std::deque<Token> &tokInput);
		double parse_factor(std::deque<Token> &tokInput);
		double parse_item(std::deque<Token> &tokInput);
};