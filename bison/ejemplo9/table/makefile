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


# MODFIIED in example 7
# Objects
OBJECTS= table.o symbol.o variable.o numericVariable.o

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
# Auxiliary files and hmtl directory are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory table"
	@rm -f $(OBJECTS) *~ 
	@echo



