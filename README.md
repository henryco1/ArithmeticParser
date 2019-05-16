# Arithmetic Parser
This repo is a C++ program that can evaluate arithmetic expressions. The user can input expressions in the terminal and the program will evaluate the expression given that it is a valid input. As of right now, this program can handle:

- Addition
- Subtraction
- Multiplication
- Division
- Exponents
- Decimals
- Negative numbers
- Parentheses

## How does it work?

At its heart, this program is a _recursive descent parser_. 
This parser has three major steps:

1.  Turning your strings into basic fundamental units that we will call tokens
2.  Creating a structure your tokens
3.  Assigning meaning to your tokens.

Turns out that these three steps represent arithmetic expressions really well:

1.  Our string is composed of numbers, operators, and groupings
2.  Evaluating our expression follows an order of operations (PEMDAS)
3.  Our expression ultimately computes to a value.

These steps can easily be turned into code with a few recursive functions and a well defined structure. The question now is how can we model an arithmetic expression?

### Context Free Grammars

A context-free grammar (CFG) is a set of rules that describe all possible strings in a language. Arithmetic expressions can easily be modeled using a CFG. We can create rules that can tell us what numbers we can work with, what operations we can use, and what order we should do our operations.

In short, CFGs are composed of nonterminal symbols and terminal symbols. Terminal symbols are actually our tokens. These are the basic units. A nonterminal symbol is a pattern of tokens. These patterns give structure to our tokens. CFGs can also include a vertical bar between terminal symbols. This vertical bar just means or.

### Creating a parser using a CFG as a model

This program is made up of separate methods that follow a rule in an expression's context-free grammar. The CFG of the parser is as follows:

> expr -> term add-op term 
> term -> factor mult-op factor 
> factor -> sign item func-op factor 
> item -> (expr) | number 
> add-op -> + | - 
> mult-op -> * | / 
> sign -> - | Ø 
> func-op -> ^ 
> number -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | .

The parser will also do error checking for invalid inputs. The program can deal with whitespaces, missing parentheses, and invalid characters like an @ sign or a letter. 
