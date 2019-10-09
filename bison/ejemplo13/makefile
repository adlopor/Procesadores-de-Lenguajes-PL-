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

# Directive for flex's library
LFLAGS = -lfl 

# Objects
OBJECTS= $(NAME).o
OBJECTS-PARSER = parser/*.o
OBJECTS-ERROR = error/*.o
OBJECTS-TABLE = table/*.o  #New in example 7

#######################################################

#Modified in example 7
$(NAME).exe :  parser-dir error-dir table-dir $(OBJECTS)
	@echo "Generating " $(NAME).exe
	@$(CPP) $(OBJECTS) $(OBJECTS-PARSER) $(OBJECTS-ERROR)  $(OBJECTS-TABLE) $(LFLAGS) -o $(NAME).exe 


# Main program
$(NAME).o: $(NAME).cpp parser-dir
	@echo "Compiling " $(NAME).cpp
	@$(CPP) $(CFLAGS) $(NAME).cpp 
	@echo

# 
parser-dir:
	@echo "Accessing directory parser" 
	@echo
	@make -C parser/
	@echo

error-dir:
	@echo "Accessing directory error" 
	@echo
	@make -C error/ 
	@echo

# New in example 7
table-dir:
	@echo "Accessing directory table" 
	@echo
	@make -C table/ 
	@echo

#######################################################
$(NAME).output: 
	@echo "Generating: " $(NAME).output
	@make -C parser/ $(NAME).output
	@echo


#######################################################
# Generate the documentation
doc: Doxyfile
	doxygen

#######################################################
# Auxiliary files and hmtl directory are deleted
# Modified in example 7
clean: 
	@echo "Deleting html"
	@rm -rf html 
	@echo "Deleting " $(OBJECTS)  $(NAME).exe  *~ 
	@rm -f $(OBJECTS) $(NAME).exe *~ 
	@echo
	@make -C parser/ clean 
	@echo
	@make -C error/ clean
	@echo
	@make -C table/ clean
	@echo



