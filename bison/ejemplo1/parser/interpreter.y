/*! 
  \file interpreter.y
  \brief Grammar file
*/

%{
#include <iostream>
#include <string>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!<  External line counter

%}

/* In case of a syntactic error, more information is shown */
%error-verbose

//! \name Grammar symbols

/* Initial grammatical symbol */
%start program 

/* Defined token */
%token NUMBER

/* Left associativity  */

/* Minimum precedence */
%left '+' '-'

/* Maximum precedence */
%left '*' '/'

%%
//! \name Grammar rules

program : stmtlist
		 { 
			/* Empty */
		 }
;

stmtlist:  /* Empty: epsilon rule */

		| stmtlist '\n'  /* Empty line */

        | stmtlist exp '\n'
            { 
				std::cout << BIYELLOW; 
				std::cout << "Correct expression " << std::endl << std::endl;
				std::cout << RESET; 
            }

        | stmtlist error '\n' 
;

exp:	NUMBER 
       { std::cout << "Number" << std::endl;}

	|	exp '+' exp 
		{ std::cout << "Plus operator" << std::endl;}

	|	exp '-' exp
		{ std::cout << "Minus operator" << std::endl;}

	|	exp '*' exp 
		{ std::cout << "Multiplication operator" << std::endl;}

	|	exp '/' exp 
		{ std::cout << "Division operator" << std::endl;}

	|	'(' exp ')'
		{ std::cout << "Parenthesis " << std::endl;}
;
 
%%

