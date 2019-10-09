# MAKEFILE for Table of symbols
# NEW in example 7

NAME=interpreter

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2


# MODFIIED in examples 7, 10, 11, 12
# Objects
OBJECTS= table.o symbol.o variable.o numericVariable.o init.o constant.o numericConstant.o \
		keyword.o

#######################################################

# Regla principal

all: $(OBJECTS)

table.o: table.cpp  table.hpp  tableInterface.hpp  symbol.hpp  symbolInterface.hpp
	@echo "Compiling " table.cpp
	@$(CPP) $(CFLAGS) table.cpp	

symbol.o: symbol.cpp symbolInterface.hpp symbol.hpp
	@echo "Compiling " symbol.cpp
	@$(CPP) $(CFLAGS) symbol.cpp	

variable.o: variable.cpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " variable.cpp
	@$(CPP) $(CFLAGS) variable.cpp	

numericVariable.o: numericVariable.cpp numericVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " numericVariable.cpp
	@$(CPP) $(CFLAGS) numericVariable.cpp		


#######################################################
# NEW in example 10
# Initialize the table of symbols.
init.o: init.cpp numericVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp table.hpp tableInterface.hpp
	$(CPP) $(CFLAGS) init.cpp	

#######################################################
# NEW in example 11
constant.o: constant.cpp constant.hpp symbol.hpp symbolInterface.hpp 
	$(CPP) $(CFLAGS) constant.cpp	

# NEW in example 11
numericConstant.o: numericConstant.cpp numericConstant.hpp constant.hpp symbol.hpp symbolInterface.hpp 
	$(CPP) $(CFLAGS) numericConstant.cpp	
#######################################################

# NEW in example 12
keyword.o: keyword.cpp keyword.hpp symbol.hpp symbolInterface.hpp 
	$(CPP) $(CFLAGS) keyword.cpp	
################################################################



#######################################################
# Auxiliary files and hmtl directory are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory table"
	@rm -f $(OBJECTS) *~ 
	@echo



