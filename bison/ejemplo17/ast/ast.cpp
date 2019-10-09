/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2017-12-5
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>


// pow
#include <math.h>

#include "ast.hpp"

#include "../table/table.hpp"

// execerror
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

// 
#include "../table/numericVariable.hpp"

#include "../table/numericConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

//
#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 
void lp::NumberNode::print()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluate() 
{ 
    return this->_number; 
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NumericVariableNode::print() 
{
  std::cout << "NumericVariableNode: " << this->_id << std::endl;
}

double lp::NumericVariableNode::evaluate() 
{ 
	// Get the identifier in the table of symbols as NumericVariable
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

	// Check if the type of the identifier is undefined
	if (n->getType() == UNDEFINED)
		execerror("Undefined variable", n->getName());

	// Return the value of the identifier
	return n->getValue();

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NumericConstantNode::print() 
{
  std::cout << "NumericVariableNode: " << this->_id << std::endl;
}

double lp::NumericConstantNode::evaluate() 
{ 
	// Get the identifier in the table of symbols as NumericConstant
	lp::NumericConstant *n = (lp::NumericConstant *) table.getSymbol(this->_id);

	// Check if the type of the identifier is undefined
	if (n->getType() == UNDEFINED)
		execerror("Undefined variable", n->getName());

	// Return the value of the identifier
	return n->getValue();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print() 
{
  std::cout << "UnaryMinusNode: "  << std::endl;
  std::cout << "-";
  this->_exp->print();
}

double lp::UnaryMinusNode::evaluate()
{

  return - this->_exp->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print() 
{
  std::cout << "UnaryPlusNode: "  << std::endl;
  this->_exp->print();
}

double lp::UnaryPlusNode::evaluate()
{
  return - this->_exp->evaluate();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print() 
{
  std::cout << "PlusNode: "  << std::endl;
  this->_left->print();
  std::cout << " + ";
  this->_right->print();
}

double lp::PlusNode::evaluate()
{
  return this->_left->evaluate() + this->_right->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print() 
{
  std::cout << "MinusNode: "  << std::endl;
  this->_left->print();
  std::cout << " - ";
  this->_right->print();
}

double lp::MinusNode::evaluate() 
{
	return this->_left->evaluate() - this->_right->evaluate();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print() 
{
	std::cout << "MultiplicationNode: "  << std::endl;
	this->_left->print();
	std::cout << " * ";
	this->_right->print();
}

double lp::MultiplicationNode::evaluate() 
{
	return this->_left->evaluate() * this->_right->evaluate();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
  std::cout << "DivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::DivisionNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

    if(rightNumber == 0.0)
      {
		execerror("Runtime error", "Division by zero");
	  }


    return leftNumber / rightNumber;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IntDivisionNode::print()
{
  std::cout << "IntDivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::IntDivisionNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

    if(rightNumber == 0.0)
      {
    execerror("Runtime error", "IntDivision by zero");
    }


    return int (leftNumber / rightNumber);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
  std::cout << "ModuloNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::ModuloNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

    if(rightNumber == 0.0)
      {
		execerror("Runtime error", "Division by zero");
	  }

    return (int) leftNumber % (int) rightNumber;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print() 
{
	std::cout << "PowerNode: "  << std::endl;
	this->_left->print();
	std::cout << " ^ ";
	this->_right->print();
}

double lp::PowerNode::evaluate() 
{
	return pow(this->_left->evaluate(), this->_right->evaluate());
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode::print() 
{
	std::cout << "BuiltinFunctionNode: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter1
	lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);


	// Apply the function to the parameter and copy the result
	return f->getFunction()(this->_exp->evaluate());
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode_0::print() 
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BuiltinFunctionNode_2::print() 
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluate() 
{
	// Get the identifier in the table of symbols as BuiltinParameter2
	lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

	// Apply the function to the parameters and copy the result
  	return f->getFunction()(this->_exp1->evaluate(),this->_exp2->evaluate());
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
  std::cout << "GreaterThanNode: " << std::endl;
  this->_left->print();
  std::cout << " > ";
  this->_right->print();
}

double lp::GreaterThanNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber > rightNumber)? 1.0 : 0.0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
  std::cout << "GreaterOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " >= ";
  this->_right->print();
}

double lp::GreaterOrEqualNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber >= rightNumber)? 1.0 : 0.0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
  std::cout << "LessThanNode: " << std::endl;
  this->_left->print();
  std::cout << " < ";
  this->_right->print();
}

double lp::LessThanNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber < rightNumber)? 1.0 : 0.0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
  std::cout << "LessOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " <= ";
  this->_right->print();
}

double lp::LessOrEqualNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber <= rightNumber)? 1.0 : 0.0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
  std::cout << "EqualNode: " << std::endl;
  this->_left->print();
  std::cout << " == ";
  this->_right->print();
}

double lp::EqualNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber == rightNumber)? 1.0 : 0.0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
  std::cout << "NotEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " != ";
  this->_right->print();
}

double lp::NotEqualNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber != rightNumber)? 1.0 : 0.0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: " << std::endl;
  this->_left->print();
  std::cout << " && ";
  this->_right->print();
}

double lp::AndNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber && rightNumber)? 1.0 : 0.0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: " << std::endl;
  this->_left->print();
  std::cout << " || ";
  this->_right->print();
}

double lp::OrNode::evaluate() 
{
    double leftNumber, rightNumber;

    leftNumber = this->_left->evaluate();
    rightNumber = this->_right->evaluate();

	return (leftNumber || rightNumber)? 1.0 : 0.0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
  std::cout << "NotNode: " << std::endl;
  std::cout << " ! ";
  this->_exp->print();
}

double lp::NotNode::evaluate() 
{
	return ! this->_exp->evaluate();
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print() 
{
  std::cout << "assignment_node: "  << std::endl;
  std::cout << this->_id << " = ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate() 
{
	// evaluate the expression
 	double value = this->_exp->evaluate();

  	// Get the identifier in the table of symbols as NumericVariable
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

	// Assignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);

	// Copy the value of the expression to allow multiple assignment: a = b = c = 2;
	// return value;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print() 
{
  std::cout << "PrintStmt: "  << std::endl;
  std::cout << " print ";
  this->_exp->print();
  std::cout << std::endl;
}


void lp::PrintStmt::evaluate() 
{
	std::cout << BIYELLOW; 
	std::cout << "Print: ";
	std::cout << RESET; 
	std::cout << this->_exp->evaluate() << std::endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print() 
{
  std::cout << "ReadStmt: "  << std::endl;
  std::cout << " read (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{
	double value;
	std::cout << BIYELLOW; 
	std::cout << "Insert a numeric value --> " ;
	std::cout << RESET; 
	std::cin >> value;

	// Get the identifier in the table of symbols as NumericVariable
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

	// Assignment the read value to the identifier in the table of symbols
	n->setValue(value);

	// Change the type of the identifier if it was undefined
	if (n->getType() == UNDEFINED)
			 n->setType(NUMERICVARIABLE);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print() 
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Consequent
  this->_stmt1->print();

 // The alternative is printed if exists
  if (this->_stmt2 != NULL)
	  this->_stmt2->print();

  std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
	if (this->_cond->evaluate() != 0.0)
     // If the condition is not zero, the consequent is run 
	  this->_stmt1->evaluate();

    // Otherwise, the alternative is run if exists
	else if (this->_stmt2 != NULL)
		  this->_stmt2->evaluate();
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print() 
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
  this->_stmt->print();

  std::cout << std::endl;
}


void lp::WhileStmt::evaluate() 
{
  // While the condition is not zero, the body is run 
  while (this->_cond->evaluate() != 0)
  {	
	  this->_stmt->evaluate();
  }

}





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::BlockStmt::print() 
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
     (*stmtIter)->print();
  }
}


void lp::BlockStmt::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print() 
{
  std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
  // Empty
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
     (*stmtIter)->print();
  }
}



void lp::AST::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}







