/*!	
	\file    ast.hpp
	\brief   Declaration of AST class
	\author  
	\date    2017-12-12
	\version 1.0
*/

#ifndef _AST_HPP_
#define _AST_HPP_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

namespace lp
{
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*!	
  \class   ExpNode
  \brief   Definition of atributes and methods of ExpNode class
  \warning Abstract class
*/
 class ExpNode 
{
  public:
	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate
	*/
    virtual void print() = 0;

	/*!	
		\brief   Evaluate the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  double
		\sa		 print
	*/
    virtual double evaluate() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumberNode
  \brief Definition of atributes and methods of NumberNode class
  \note  NumberNode Class publicly inherits from ExpNode class
*/
class NumberNode : public ExpNode 
{
 private: 	
   double _number; //!< \brief number of the NumberNode
 
 public:

/*!		
	\brief Constructor of NumberNode
	\param value: double
	\post  A new NumberNode is created with the value of the parameter
	\note  Inline function
*/
  NumberNode(double value)
	{
	    this->_number = value;
	}

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumericVariableNode
  \brief Definition of atributes and methods of NumericVariableNode class
  \note  NumericVariableNode Class publicly inherits from ExpNode class
*/
class NumericVariableNode : public ExpNode 
{

 private:
  std::string _id; //!< Name of the NumericVariableNode

public:

/*!		
	\brief Constructor of NumericVariableNode
	\param value: double
	\post  A new NumericVariableNode is created with the name of the parameter
	\note  Inline function
*/
  NumericVariableNode(std::string value)
	{
		this->_id = value; 
	}

/*!
	\brief   Print the Variable
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the Variable
	\return  double
	\sa		 print
*/
  double evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumericConstantNode
  \brief Definition of atributes and methods of NumericConstantNode class
  \note  NumericConstantNode Class publicly inherits from ExpNode class
*/
class NumericConstantNode : public ExpNode 
{

 private:
  std::string _id; //!< Name of the NumericConstantNode

public:

/*!		
	\brief Constructor of NumericVariableNode
	\param value: double
	\post  A new NumericVariableNode is created with the name of the parameter
*/
  NumericConstantNode(std::string value)
	{
		this->_id = value; 
	}


/*!
	\brief   Print the NumericConstantNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the NumericConstantNode
	\return  double
	\sa		 print
*/
  double evaluate();

};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of ExpNode
*/
class UnaryOperatorNode : public ExpNode 
{
 protected:
  ExpNode *_exp;  //!< Child expression

 public:

/*!		
	\brief Constructor of UnaryOperatorNode links the node to it child,
           and stores the character representation of the operator.
	\param expression: pointer to ExpNode
	\post  A new OperatorNode is created with the parameters
	\note  Inline function
*/
  UnaryOperatorNode(ExpNode *expression)
	{
		this->_exp = expression;
	}
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusNode
  \brief   Definition of atributes and methods of UnaryMinusNode class
  \note    UnaryMinusNode Class publicly inherits from UnaryOperatorNode class
*/
class UnaryMinusNode : public UnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryMinusNode uses UnaryOperatorNode's constructor as member initializer.
	\param expression: pointer to ExpNode
	\post  A new UnaryMinusNode is created with the parameter
	\note  Inline function: the ExpNode's constructor is used ad member initializer
*/
  UnaryMinusNode(ExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    UnaryPlusNode Class publicly inherits from UnaryOperatorNode class
*/
class UnaryPlusNode : public UnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryPlusNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryPlusNode is created with the parameter
*/
  UnaryPlusNode(ExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluate();
};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   OperatorNode
  \brief   Definition of atributes and methods of OperatorNode class
  \note    OperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the print and evaluate methods of ExpNode
*/
class OperatorNode : public ExpNode 
{
protected:
    ExpNode *_left;    //!< Left expression
    ExpNode *_right;   //!< Right expression

public:
/*!		
	\brief Constructor of OperatorNode links the node to its children,
           and stores the character representation of the operator.
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new OperatorNode is created with the parameters
*/
    OperatorNode(ExpNode *L, ExpNode *R)
	{
	    this->_left  = L;
    	this->_right = R;
	}

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusNode
  \brief   Definition of atributes and methods of PlusNode class
  \note    PlusNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class PlusNode : public OperatorNode 
{
  public:
/*!		
	\brief Constructor of PlusNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PlusNode is created with the parameter
*/
  PlusNode(ExpNode *L, ExpNode *R) : OperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PlusNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PlusNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MinusNode
  \brief   Definition of atributes and methods of MinusNode class
  \note    MinusNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class MinusNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of MinusNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MinusNode is created with the parameter
*/
  MinusNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MinusNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the MinusNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MultiplicationNode
  \brief   Definition of atributes and methods of MultiplicationNode class
  \note    MultiplicationNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class MultiplicationNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of MultiplicationNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MultiplicationNode is created with the parameter
*/
  MultiplicationNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MultiplicationNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the MultiplicationNode
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DivisionNode
  \brief   Definition of atributes and methods of DivisionNode class
  \note    DivisionNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class DivisionNode : public OperatorNode 
{
  public:
/*!		
	\brief Constructor of DivisionNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new DivisionNode is created with the parameter
*/
  DivisionNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the DivisionNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the DivisionNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ModuloNode
  \brief   Definition of atributes and methods of ModuloNode class
  \note    ModuloNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class ModuloNode : public OperatorNode 
{
  public:
/*!		
	\brief Constructor of ModuloNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new ModuloNode is created with the parameter
*/
  ModuloNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the ModuloNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ModuloNode
	\return  double
	\sa		 print
*/
  double evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PowerNode
  \brief   Definition of atributes and methods of PowerNode class
  \note    PowerNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class PowerNode : public OperatorNode 
{
  public:
/*!		
	\brief Constructor of PowerNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PowerNode is created with the parameter
*/
  PowerNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PowerNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PowerNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode
  \brief   Definition of atributes and methods of BuiltinFunctionNode class
  \note    BuiltinFunctionNode Class publicly inherits from ExpNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode : public ExpNode 
{
  private:
	std::string _id; //!< Name of the BuiltinFunction
	ExpNode *_exp;  //!< Argument of the BuiltinFunction

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode
	\param id: string, name of the BuiltinFunction
	\param expression: pointer to ExpNode, argument of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameters
*/
  BuiltinFunctionNode(std::string id, ExpNode *expression)
	{
		this->_id = id;
		this->_exp = expression;
	}

/*!
	\brief   Print the BuiltinFunctionNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_0
  \brief   Definition of atributes and methods of BuiltinFunctionNode_0 class
  \note    BuiltinFunctionNode_0 Class publicly inherits from ExpNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_0 : public ExpNode 
{
  private: 
	std::string _id; //!< Name of the BuiltinFunction_0
	
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_0
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameter
*/
  BuiltinFunctionNode_0(std::string id)
	{
		this->_id = id;
	}

/*!
	\brief   Print the BuiltinFunctionNode_0
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode_0
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_2
  \brief   Definition of atributes and methods of BuiltinFunctionNode_2 class
  \note    BuiltinFunctionNode_2 Class publicly inherits from OperatoExpNoderNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_2 : public ExpNode 
{
 private:
	std::string _id; //!< Name of the BuiltinFunction_2
	ExpNode *_exp1; //!< First argument of the BuiltinFunction_2
	ExpNode *_exp2; //!< Second argument of the BuiltinFunction_2

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_2
	\param id: string, name of the BuiltinFunction_2
	\param expression1: pointer to ExpNode, first argument of the BuiltinFunctionNode
	\param expression2: pointer to ExpNode, second argument of the BuiltinFunctionNode
	\post  A new BuiltinFunctionNode_2 is created with the parameters
*/
  BuiltinFunctionNode_2(std::string id,ExpNode *expression1,ExpNode *expression2)
	{
		this->_id = id;
		this->_exp1 = expression1;
		this->_exp2 = expression2;
	}

/*!
	\brief   Print the BuiltinFunctionNode_2
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the BuiltinFunctionNode_2
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterThanNode
  \brief   Definition of atributes and methods of GreaterThanNode class
  \note    GreaterThanNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterThanNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterThanNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterThanNode is created with the parameter
*/
  GreaterThanNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the GreaterThanNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the GreaterThanNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterOrEqualNode
  \brief   Definition of atributes and methods of GreaterOrEqualNode class
  \note    GreaterOrEqualNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterOrEqualNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterOrEqualNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterOrEqualNode is created with the parameter
*/
  GreaterOrEqualNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the GreaterOrEqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the GreaterOrEqualNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessThanNode
  \brief   Definition of atributes and methods of LessThanNode class
  \note    LessThanNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessThanNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of LessThanNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessThanNode is created with the parameter
*/
  LessThanNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the LessThanNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the LessThanNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessOrEqualNode
  \brief   Definition of atributes and methods of LessOrEqualNode class
  \note    LessThanNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessOrEqualNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of LessOrEqualNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessOrEqualNode is created with the parameter
*/
  LessOrEqualNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the LessOrEqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the LessOrEqualNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EqualNode
  \brief   Definition of atributes and methods of EqualNode class
  \note    EqualNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class EqualNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of EqualNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new EqualNode is created with the parameter
*/
  EqualNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the EqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the EqualNode
	\return  double
	\sa		 print
*/
  double evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   NotEqualNode
  \brief   Definition of atributes and methods of NotEqualNode class
  \note    NotEqualNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class NotEqualNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of NotEqualNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new NotEqualNode is created with the parameter
*/
  NotEqualNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the NotEqualNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the NotEqualNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AndNode
  \brief   Definition of atributes and methods of AndNode class
  \note    AndNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class AndNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  AndNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the AndNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the AndNode
	\return  double
	\sa		 print
*/
  double evaluate();
};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   OrNode
  \brief   Definition of atributes and methods of OrNode class
  \note    OrNode Class publicly inherits from OperatorNode class 
		   and adds its own print and evaluate functions
*/
class OrNode : public OperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  OrNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the OrNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the OrNode
	\return  double
	\sa		 print
*/
  double evaluate();
};



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NotNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    NotNode Class publicly inherits from UnaryOperatorNode class
*/
class NotNode : public UnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of NotNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryPlusNode is created with the parameter
*/
  NotNode(ExpNode *expression): UnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the NotNode
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the NotNode
	\return  double
	\sa		 print
*/
  double evaluate();
};





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   Statement
  \brief   Definition of atributes and methods of Statement class
  \warning Abstract class
*/

class Statement {
 public:

/*!	
	\brief   Print the Statement
	\note    Virtual function: can be redefined in the heir classes
	\return  double
	\sa		 print
*/

  virtual void print() {}

/*!	
	\brief   Evaluate the Statement
	\warning Pure virtual function: must be redefined in the heir classes
	\return  double
	\sa		 print
*/
  virtual void evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AssignmentStmt
  \brief   Definition of atributes and methods of AssignmentStmt class
  \note    AssignmentStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class AssignmentStmt : public Statement 
{
 private:
  std::string _id;    //!< Name of the variable of the assignment statement
  ExpNode *_exp; //!< Expresssion the assignment statement

 public:

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new AssignmentStmt is created with the parameters
*/
  AssignmentStmt(std::string id, ExpNode *expression): _id(id), _exp(expression)
	{
		// Empty
	}

/*!
	\brief   Print the AssignmentStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the AssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStmt
  \brief   Definition of atributes and methods of PrintStmt class
  \note    PrintStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
  \warning  In this class, print and evaluate functions have the same meaning.
*/
class PrintStmt: public Statement 
{
 private:
  ExpNode *_exp; //!< Expresssion the print statement

 public:
/*!		
	\brief Constructor of PrintStmt 
	\param expression: pointer to ExpNode
	\post  A new PrintStmt is created with the parameter
*/
  PrintStmt(ExpNode *expression)
	{
		this->_exp = expression;
	}

/*!
	\brief   Print the PrintStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the PrintStmt
	\return  double
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStmt
  \brief   Definition of atributes and methods of ReadStmt class
  \note    ReadStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class ReadStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStmt
	

  public:
/*!		
	\brief Constructor of ReadStmt
	\param id: string, name of the variable of the ReadStmt
	\post  A new ReadStmt is created with the parameter
*/
  ReadStmt(std::string id)
	{
		this->_id = id;
	}

/*!
	\brief   Print the ReadStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ReadStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EmptyStmt
  \brief   Definition of atributes and methods of EmptyStmt class
  \note    EmptyStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class EmptyStmt : public Statement 
{
  // No attributes

  public:
/*!		
	\brief Constructor of  WhileStmt
	\post  A new EmptyStmt is created 
*/
  EmptyStmt()
	{
		// Empty
	}


/*!
	\brief   Print the EmptyStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the EmptyStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AST
  \brief   Definition of atributes and methods of AST class
*/
class AST {
 private:
  std::list<Statement *> *stmts;  //!< List of statements

 public:

/*!		
	\brief Constructor of PrintStmt 
	\param stmtList: pointer to a list of pointers to Statement
	\post  A new PrintStmt is created with the parameter
*/
  AST(std::list<Statement *> *stmtList): stmts(stmtList)
	{
		// Empty
	}

/*!
	\brief   print the AST
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   evaluate the AST
	\return  double
	\sa		 print
*/
  void evaluate();
};

// End of name space lp
}



// End of _AST_HPP_
#endif




