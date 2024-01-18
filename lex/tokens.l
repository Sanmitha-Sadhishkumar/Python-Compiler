%option yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../yacc/expressions.tab.h"
#include "../C_routines/SymbolTable.h"


%}

id [a-zA-Z_][a-zA-Z_0-9]*

INT [-]?[0-9]+
FLOAT [-]?[0-9]+([.][0-9]+)?([Ee][+-]?[0-9]+)?
bool "True" | "False"
str (\"([^\"\\\\]|\\\\.)*\")|('([^'\\\\]|\\\\.)*')

assign [+/%*&|^]?= 
arith [+-/%*] 
relop ">"|"<"|"=="|">="|"<="|"!="

%%

"if"        {yylval.key = strdup(yytext); return IF;}

"else"      {yylval.key = strdup(yytext); return ELSE;}

"elif"      {yylval.key = strdup(yytext); return ELIF;}

"True"      {yylval.key = strdup(yytext); return TRUE;}

"False"     {yylval.key = strdup(yytext); return FALSE;}

{INT}       {int a = installLit(yytext,"INT"); yylval.value = strdup(yytext); return INT;}

{str}       {int a = installLit(yytext,"STR"); yylval.value = strdup(yytext); return LITERAL;}

{FLOAT}     {int a = installLit(yytext,"FLOAT"); yylval.value = strdup(yytext); return FLOAT;}

{assign}    { yylval.op = strdup(yytext); return assign; }
"//="       { yylval.op = strdup(yytext); return assign; }
"**="       { yylval.op = strdup(yytext); return assign; }
">>="       { yylval.op = strdup(yytext); return assign; }
"<<="       { yylval.op = strdup(yytext); return assign; }

{arith}     { yylval.op = strdup(yytext); return arith;}
"//"        { yylval.op = strdup(yytext); return arith; }
"-"         { yylval.op = strdup(yytext); return "-"; }
"**"        { yylval.op = strdup(yytext); return arith; }

"and"       {yylval.op = strdup(yytext); return AND;}
"or"        {yylval.op = strdup(yytext); return OR;}
"not"       {yylval.op = strdup(yytext); return NOT;}

"in"        {yylval.op = strdup(yytext); return membership;}
"not in"    {yylval.op = strdup(yytext); return membership;}

"is"        {yylval.op = strdup(yytext); return identity;}
"is not"    {yylval.op = strdup(yytext); return identity;}

{relop}     {yylval.op = strdup(yytext); return relop;}

"&"         {yylval.op = strdup(yytext); return bitwise;}
"|"         {yylval.op = strdup(yytext); return bitwise;}
"^"         {yylval.op = strdup(yytext); return bitwise;}
">>"        {yylval.op = strdup(yytext); return bitwise;}
"<<"        {yylval.op = strdup(yytext); return bitwise;}

":"         {yylval.delim = strdup(yytext); return COLON;}
"\t"+       {yylval.delim = strdup(yytext); return SPACE;}
"    "        {yylval.delim = strdup(yytext); return SPACE;}
"\n"        {yylval.delim = strdup(yytext); return NL;}
"("         {yylval.delim = strdup(yytext); return "(";}
")"         {yylval.delim = strdup(yytext); return ")";}

{id}        {int a = installID(yytext, "ID"); yylval.lexeme = strdup(yytext); return id; }

<<EOF>>     {saveST(); return 0;}

%%

int yywrap(){
  return 1;
}
