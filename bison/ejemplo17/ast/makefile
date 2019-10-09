# Makefile for error
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

# Objects
OBJECTS= ast.o

# Includes
INCLUDES = ../includes

#######################################################

# Regla principal

all: $(OBJECTS)


# Error recovery functions 
ast.o: ast.cpp ast.hpp $(INCLUDES)/macros.hpp ../error/error.hpp \
	../table/table.hpp  ../table/numericConstant.hpp \
	../table/builtinParameter0.hpp ../table/builtinParameter1.hpp ../table/builtinParameter2.hpp
	@echo "Compiling " ast.cpp
	@$(CPP) $(CFLAGS) ast.cpp
	@echo



#######################################################
# Auxiliary files and hmtl directory are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory ast"
	@rm -f $(OBJECTS) *~ 
	@echo

