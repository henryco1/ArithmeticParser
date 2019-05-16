#include <string>
#include <cmath>

class Token {
	/*
	The token class represents the smallest relevant units 
	that can be thought of as base cases for the recursive parser. 

	Each token has value and helper methods for getting values and 
	token validation
	*/
	public:
		Token(std::string data) {value = data;};
		bool is_terminal(std::string input) {return (input == get_value()) ? true : false;}
		std::string get_value() {return value;}
		double get_double() {
			std::size_t strSize;
			double num = stod(value, &strSize);
			return num;
		}
	private:
		std::string value;
};