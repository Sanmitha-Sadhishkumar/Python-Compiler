
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     id = 258,
     ID = 259,
     LITERAL = 260,
     FLOAT = 261,
     INT = 262,
     AND = 263,
     OR = 264,
     NOT = 265,
     PLUS = 266,
     MINUS = 267,
     MUL = 268,
     DIV = 269,
     MOD = 270,
     EXP = 271,
     FDIV = 272,
     LT = 273,
     GT = 274,
     LTE = 275,
     GTE = 276,
     DEQ = 277,
     NE = 278,
     EQ = 279,
     AEQ = 280,
     SEQ = 281,
     MEQ = 282,
     DIEQ = 283,
     FDEQ = 284,
     EEQ = 285,
     MOEQ = 286,
     BLEQ = 287,
     BREQ = 288,
     IS = 289,
     ISN = 290,
     IN = 291,
     NIN = 292,
     LSHIFT = 293,
     RSHIFT = 294,
     BAND = 295,
     BOR = 296,
     BXOR = 297,
     BNOT = 298,
     IF = 299,
     ELSE = 300,
     ELIF = 301,
     WHILE = 302,
     FOR = 303,
     TRUE = 304,
     FALSE = 305,
     DELIMITER = 306,
     COLON = 307,
     TAB = 308,
     NL = 309,
     SPACE = 310,
     COMMA = 311,
     LISTO = 312,
     LISTC = 313,
     TUPLEO = 314,
     TUPLEC = 315,
     SETO = 316,
     SETC = 317
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 15 "expressions.y"

    char *lexeme;
    char *value;
    double dvalue;
    struct SyntaxTree *Sy;
    int ivalue;
    char *op;
    char *key;
    char *delim;



/* Line 1676 of yacc.c  */
#line 127 "expressions.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


