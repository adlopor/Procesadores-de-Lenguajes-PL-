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
OBJECTS= error.o

# Includes
INCLUDES = ../includes

#######################################################

# Regla principal

all: $(OBJECTS)


# Error recovery functions 
error.o: error.cpp error.hpp $(INCLUDES)/macros.hpp
	@echo "Compiling " error.cpp
	@$(CPP) $(CFLAGS) error.cpp
	@echo



#######################################################
# Auxiliary files and hmtl directory are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory error"
	@rm -f $(OBJECTS) *~ 
	@echo

