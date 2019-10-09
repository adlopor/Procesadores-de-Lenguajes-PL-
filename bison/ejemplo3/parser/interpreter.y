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


extern int lineNumber; //!< External line counter

/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/
%}

/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program


/* Defined token */

/* Minimum precedence */

/*******************************************/
/* NEW in example 3 */
%token NEWLINE
/*******************************************/

%token NUMBER

/* Left associativity */

/*******************************************/
/* MODIFIED in example 3 */
%left PLUS MINUS 

%left MULTIPLICATION DIVISION

%left LPAREN RPAREN

// Maximum precedence 
%nonassoc  UNARY
/*******************************************/

%%
//! \name Grammar rules

program : stmtlist
		 { 
			// Empty
		 }
;


		/* MODIFIED in example 3*/ 
stmtlist:  /* empty: epsilon rule */

		| stmtlist NEWLINE     /* empty line */

        | stmtlist exp NEWLINE
            { 
				std::cout << BIYELLOW; 
				std::cout << "Correct expression " << std::endl << std::endl;
				std::cout << RESET; 
            }

        | stmtlist error NEWLINE 
;
 
		/* MODIFIED in example 3*/ 
exp:	NUMBER 
		{ std::cout << "Number" << std::endl; }

	|	exp PLUS exp 
		{ std::cout << "Plus operator" << std::endl; }

	|	exp MINUS exp
		{ std::cout << "Minus operator" << std::endl; }

	|	exp MULTIPLICATION exp 
		{ std::cout << "Multiplication operator" << std::endl; }

	|	exp DIVISION exp 
		{ std::cout << "Division operator" << std::endl; }

	|	LPAREN exp RPAREN
		{ std::cout << "Parenthesis " << std::endl; }

		/* NEW in example 3 */ 

    | 	PLUS exp %prec UNARY
		{ std::cout << "Unary plus operator" << std::endl; }

    | 	MINUS exp %prec UNARY
		{ std::cout << "Unary minus operator" << std::endl; }
;

 
%%




