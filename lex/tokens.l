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

{id}        {int a = installID(yytext, "ID"); yylval.lexeme = strdup(yytext); return id; }

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

"and"       {yylval.op = strdup(yytext); return logical;}
"or"        {yylval.op = strdup(yytext); return logical;}
"not"       {yylval.op = strdup(yytext); return logical;}

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

<<EOF>>     {saveST(); return 0;}

%%

int yywrap(){
  return 1;
}
