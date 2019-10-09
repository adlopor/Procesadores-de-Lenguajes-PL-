/*!	
	\file    init.cpp
	\brief   Code of the function for the initialization of table of symbols
	\author  
	\date    2017-12-20
	\version 1.0
*/

#include "init.hpp"

#include "table.hpp"


//  NEW in example 11 
#include "numericConstant.hpp"

//  NEW in example 12
#include "keyword.hpp"

//  NEW in example 13
#include "builtinParameter1.hpp"


// NEW  in example 14
#include "builtinParameter0.hpp"
#include "builtinParameter2.hpp"


//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"


//////////////////////////////////////////////////////////////////////////////////


void init(lp::Table &t)
{
 int i;

 lp::NumericConstant *n;

 // The predefined numeric constants are installed in the table of symbols
 for (i=0; constants[i].name.compare("")!=0; i++)
	{
		// The  Predefined numeric constant is inserted into the symbol table

		 n = new lp::NumericConstant(constants[i].name,
									 CONSTANT,
									 NUMERICCONSTANT,
									 constants[i].value);

		// A pointer to the new NumericConstant is inserted into the table of symbols
		t.installSymbol(n);
	}


  //////////////////////////////////////////////

 lp::Keyword *k;

 // The predefined numeric constants are installed in the table of symbols
 for (i=0; keywords[i].name.compare("")!=0; i++)
	{
		// The  Keywords numeric is inserted into the symbol table

		 k = new lp::Keyword(keywords[i].name,
							 keywords[i].token);

		// A pointer to the new Keyword is inserted into the table of symbols
		t.installSymbol(k);
	}


  //////////////////////////////////////////////


 lp::BuiltinParameter1 *f;

 // The predefined functions with 1 parameter are installed in the table of symbols
 for (i=0; functions[i].name.compare("")!=0; i++)
	{
		// The  Keywords numeric is inserted into the symbol table

		 f = new lp::BuiltinParameter1(functions[i].name,
									   BUILTIN,   // Token
									   1,		  // Number of parameters
									   functions[i].function);

		// A pointer to the new Keyword is inserted into the table of symbols
		t.installSymbol(f);
	}


  //////////////////////////////////////////////
  // NEW in example 14

 lp::BuiltinParameter0 *f0;

 // The predefined functions with 0 parameters are installed in the table of symbols
 for (i=0; functions_0[i].name.compare("")!=0; i++)
	{
		 f0 = new lp::BuiltinParameter0(functions_0[i].name,
									   BUILTIN,   // Token
									   0,		  // Number of parameters
									   functions_0[i].function);

		// A pointer to the new Keyword is inserted into the table of symbols
		t.installSymbol(f0);
	}




  //////////////////////////////////////////////
  // NEW in example 14

 lp::BuiltinParameter2 *f2;

 // The predefined functions with 2 parameters are installed in the table of symbols
 for (i=0; functions_2[i].name.compare("")!=0; i++)
	{
		 f2 = new lp::BuiltinParameter2(functions_2[i].name,
									   BUILTIN,   // Token
									   2,		  // Number of parameters
									   functions_2[i].function);

		// A pointer to the new Keyword is inserted into the table of symbols
		t.installSymbol(f2);
	}


}

