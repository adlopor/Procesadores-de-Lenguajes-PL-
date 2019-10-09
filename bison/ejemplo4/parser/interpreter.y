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

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union
{
  double number;  
}

/* Data type of the non-terminal symbol "exp" */
%type <number> exp
/*******************************************/

/* Defined token */

/* Minimum precedence */

/*******************************************/
/* NEW in example 3 */
%token NEWLINE
/*******************************************/

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

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

		/* MODIFIED in example 4 */ 
stmtlist:  /* empty: epsilon rule */

		| stmtlist NEWLINE     /* empty line */

        | stmtlist exp NEWLINE
            { 
				std::cout << BIYELLOW; 
				std::cout << "Result: ";
				std::cout << RESET; 
				std::cout << $2 << std::endl << std::endl;
            }

        | stmtlist error NEWLINE
;

		/* MODIFIED in example 4 */ 
 exp:	NUMBER 
		{ $$ = $1; }

	| 	exp PLUS exp 
		{ $$ = $1 + $3; }

	| 	exp MINUS exp
      	{ $$ = $1 - $3; }

	| 	exp MULTIPLICATION exp 
		{ $$ = $1 * $3; }

	| 	exp DIVISION exp
		{ $$ = $1 / $3; }

	| 	LPAREN exp RPAREN
       	{ $$ = $2; }

		/* NEW in example 3 and MODIFIED in example 4 */

  	| 	PLUS exp %prec UNARY
		{ $$ = +$2; }

	| 	MINUS exp %prec UNARY
		{ $$ = -$2; }
;


%%




