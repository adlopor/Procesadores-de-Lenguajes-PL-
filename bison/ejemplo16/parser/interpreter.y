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

/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"

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

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
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
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

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
  char * identifier; 				 /* NEW in example 7 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */
}

/* Type of the non-terminal symbols */
%type <expNode> exp 
%type <stmts> stmtlist
%type <st> stmt asgn print read 
%type <prog> program

// Defined token 

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

/* NEW in example 9 */
%token PRINT READ


/* NEW in example 7 */
%right ASSIGNMENT

/* NEW in example 14 */
%token COMMA

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

/* MODIFIED in examples 11, 13 */
%token <identifier> VARIABLE NUMERICVARIABLE UNDEFINED CONSTANT NUMERICCONSTANT BUILTIN

/* Left associativity */

/*******************************************************/
/* NEW in example 15 */
%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN  EQUAL NOT_EQUAL

%left NOT
/*******************************************************/

/* MODIFIED in example 3 */
%left PLUS MINUS 

/* MODIFIED in example 5 */
%left MULTIPLICATION DIVISION MODULO

%left LPAREN RPAREN

%nonassoc  UNARY

// Maximum precedence 
/* MODIFIED in example 5 */
%right POWER


%%
//! \name Grammar rules

/* MODIFIED  Grammar in example 16 */

program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new std::list<lp::Statement *>(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

 			//$2->evaluate();
           }


        | stmtlist error 
           { 
			// just copy up the stmtlist when an error occurs
			$$ = $1;

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
           } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn  SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| print SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| read SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
;



asgn:   VARIABLE ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	| CONSTANT ASSIGNMENT exp 
		{   
			// Get the identifier in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

 			execerror("Semantic error in assignment: it is not allowed to modify a constant ",
				       n->getName());
		}
;


print:  PRINT exp 
		{
			// Create a new print node
			 $$ = new lp::PrintStmt($2);
		}
;	

read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt($3);

		}
	| READ LPAREN CONSTANT RPAREN  
		{   
			// Get the identifier in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($3);

 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",
				       n->getName());
		}
;	


exp:	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}

	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		 }

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	   }

	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }

  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}

	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	

		  $$ = new lp::ModuloNode($1, $3);
       }

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}

	| 	asgn
		{
			// Default action: allow multiple assigment -> a = b = c = 2 * d;
			// $$ = $1;
		}

	 | VARIABLE
		{
		  // Create a new numeric variable node	
		  $$ = new lp::NumericVariableNode($1);
		}

	 | CONSTANT
		{
			// Get the identifier in the table of symbols as NumericConstant
			lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol($1);

			// Check if the type of the identifier is NUMERICONSTANT
			if (n->getType() == NUMERICCONSTANT)
				{
				  // Create a new numericConstant node	
					$$ = new lp::NumericConstantNode($1);
				}
			else			 
	  			 execerror("Undefined constant", n->getName());		
		}

	| BUILTIN LPAREN exp RPAREN
		{
		  // Create a new Builtin Function with 1 parameter node	
			$$ = new lp::BuiltinFunctionNode($1,$3);
		}

	| BUILTIN LPAREN RPAREN
		{
		  // Create a new Builtin Function with 0 parameters node	
			$$ = new lp::BuiltinFunctionNode_0($1);
		}

	| BUILTIN LPAREN exp COMMA exp RPAREN
		{
		  // Create a new Builtin Function with 2 parameters node	
			$$ = new lp::BuiltinFunctionNode_2($1,$3,$5);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}

    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}


;


%%



