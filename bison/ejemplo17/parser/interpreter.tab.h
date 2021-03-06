/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    LETFCURLYBRACKET = 260,
    RIGHTCURLYBRACKET = 261,
    PRINT = 262,
    READ = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    ASSIGNMENT = 267,
    NUMBER = 268,
    VARIABLE = 269,
    NUMERICVARIABLE = 270,
    UNDEFINED = 271,
    CONSTANT = 272,
    NUMERICCONSTANT = 273,
    BUILTIN = 274,
    OR = 275,
    AND = 276,
    GREATER_OR_EQUAL = 277,
    LESS_OR_EQUAL = 278,
    GREATER_THAN = 279,
    LESS_THAN = 280,
    EQUAL = 281,
    NOT_EQUAL = 282,
    NOT = 283,
    PLUS = 284,
    MINUS = 285,
    MULTIPLICATION = 286,
    DIVISION = 287,
    MODULO = 288,
    INT_DIVISION = 289,
    LPAREN = 290,
    RPAREN = 291,
    UNARY = 292,
    POWER = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 116 "interpreter.y" /* yacc.c:1909  */

  double number;  
  char * identifier; 				 /* NEW in example 7 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 102 "interpreter.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
