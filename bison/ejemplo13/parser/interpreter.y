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


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

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
%type <number> exp asgn
/*******************************************/

/* Defined tokens */

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/


/* NEW in example 9 */
%token PRINT READ

/* NEW in example 7 */
%right ASSIGNMENT


/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

/* MODIFIED in examples 11, 13 */
%token <identifier> VARIABLE NUMERICVARIABLE UNDEFINED CONSTANT NUMERICCONSTANT BUILTIN

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

%%
//! \name Grammar rules

program : stmtlist {  }
;

/* MODIFIED in example 9 */ 
stmtlist:	/* empty: epsilon rule */

        | stmtlist stmt 

        | stmtlist error 
;

/* NEW rules in example 9 */
stmt: SEMICOLON  /* Empty statement: ";" */

	| asgn SEMICOLON

	| print SEMICOLON

	| read SEMICOLON
;

	     /* NEW in example 8 */ 
asgn:   VARIABLE ASSIGNMENT exp 
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

	   /* NEW in example 11 */ 
	| CONSTANT ASSIGNMENT exp 
		{   
			/* Get the identifier in the table of symbols as NumericConstant */
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

 			execerror("Semantic error in assignment: it is not allowed to modify a constant ",
				       n->getName());
		}
;


/* NEW rule in example 9 */
print:  PRINT exp 
		{
			std::cout << BIYELLOW; 
			std::cout << "Print: ";
			std::cout << RESET; 
			std::cout << $2 << std::endl << std::endl;
		}
;		

		/* NEW rule in example 9 */
read:  READ LPAREN VARIABLE RPAREN  
		{
			double value;
			std::cout << BIYELLOW; 
			std::cout << "Insert a numeric value --> " ;
			std::cout << RESET; 
			std::cin >> value;

			/* Get the identifier in the table of symbols as NumericVariable */
			lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol($3);

			/* Assignment the read value to the identifier in the table of symbol */
			n->setValue(value);

			/* Change the type of the identifier if it was undefined */
			if (n->getType() == UNDEFINED)
				 n->setType(NUMERICVARIABLE);
		}

  	  /* NEW rule in example 11 */
	| READ LPAREN CONSTANT RPAREN  
		{   
			// Get the identifier in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($3);

 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
				       n->getName());
		}
;


 		/* MODIFIED in examples 4 and 8 */ 
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

	|	exp POWER exp 
     	{ $$ = pow($1,$3); }


	   /* NEW in example 8 */
     | asgn

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

  	  /* NEW rule in example 11 */
	 | CONSTANT
		{
			// Get the identifier in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

			// Check if the type of the identifier is NUMERICCONSTANT
			if (n->getType() == NUMERICCONSTANT)
				{
					// Copy the value of the identifier
					$$ = n->getValue();
				}
			else			 
	  			 execerror("Undefined constant", n->getName());		
		}

  	  /* NEW rule in example 13 */
	| BUILTIN LPAREN exp RPAREN
		{
			// Get the identifier in the table of symbols as BuiltinParameter1
			lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol($1);

			// Apply the function to the parameters and copy the result
	    	$$ = f->getFunction()($3);

		}
;


%%




