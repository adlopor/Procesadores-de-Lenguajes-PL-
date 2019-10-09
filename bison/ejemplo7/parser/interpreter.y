/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"
/*******************************************/


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

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Externa Table of Symbols

%}
/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
  double number;  
  char * identifier;   /* NEW in example 7 */
}

/* Data type of the non-terminal symbol "exp" */
%type <number> exp
/*******************************************/

/* NEW in example 7 */
%token <identifier> VARIABLE NUMERICVARIABLE UNDEFINED 

/* Defined token */

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

/* NEW in example 7 */
%right ASSIGNMENT

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

/* Left associativity */

/*******************************************/
/* MODIFIED in example 3 */
%left PLUS MINUS 

/* MODIFIED in example 5 */
%left MULTIPLICATION DIVISION MODULO

%left LPAREN RPAREN

%nonassoc  UNARY

/* Maximum precedence  */
/* MODIFIED in example 5 */
%right POWER

/*******************************************/

%%
//! \name Grammar rules

program : stmtlist {  }
;

		/* MODIFIED in example 5 */ 
stmtlist:  /* empty: epsilon rule */

		| stmtlist SEMICOLON     /* empty line */

        | stmtlist exp SEMICOLON
            { 
				std::cout << BIYELLOW; 
				std::cout << "Result: ";
				std::cout << RESET; 
				std::cout << $2 << std::endl << std::endl;
            }

        | stmtlist error SEMICOLON
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
		{	
			/* MODIFIED in example 6 */ 
	         if ($3 == 0.0) 
  				 execerror("Runtime error in division", "Division by zero");
			 else 
    	         $$ = $1 / $3;
	   }

	| 	LPAREN exp RPAREN
       	{ $$ = $2; }

		/* NEW in example 3 and MODIFIED in example 4 */
  	| 	PLUS exp %prec UNARY
		{ $$ = +$2; }

	| 	MINUS exp %prec UNARY
		{ $$ = -$2; }


		/* NEW in example 5 */
	|	exp MODULO exp 
		{
			/* MODIFIED in example 6 */ 
	         if ($3 == 0.0) 
  				 execerror("Runtime error in modulo", "Division by zero");
			 else 
    	         $$ = (int) $1 % (int) $3;
       }

		/* NEW in example 5 */
	|	exp POWER exp 
     	{ $$ = pow($1,$3); }


		/* NEW in example 7 */
	|  VARIABLE ASSIGNMENT exp 
		{   
			/* Multiple assignments in the same sentence */

			/* Get the identifier in the table of symbols as NumericVariable */
			lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol($1);
			
			/* 
			 Assignment the value of expression to the identifier in the table of symbol
			 and copy the value of the identifier
			*/
			n->setValue($3);

			/* Change the type of the identifier if it was UNDEFINED */
			if (n->getType() == UNDEFINED)
				 n->setType(NUMERICVARIABLE);

			/* Copy the value of the expression to allow multiple assignment: a = b = c = 2; */
			$$ = $3;
		}

		/* NEW in example 7 */
	 | VARIABLE
		{
			/* Get the identifier in the table of symbols as NumericVariable */
			lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol($1);

			// Check if the type of the identifier is undefined
			if (n->getType() == UNDEFINED)
	  			 execerror("Undefined variable", n->getName());
			else			 
				// Copy the value of the identifier
				$$ = n->getValue();
		}
;


%%




