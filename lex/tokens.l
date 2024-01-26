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

list \[.*\]
tuple \(.*\)
set \{.+\}
dict \{(.+:.+,?)*\}

%%

"if"        {yylval.key = strdup(yytext); return IF;}

"else"      {yylval.key = strdup(yytext); return ELSE;}

"while"     {yylval.key = strdup(yytext); return WHILE;}

"elif"      {yylval.key = strdup(yytext); return ELIF;}

"True"      {yylval.key = strdup(yytext); return TRUE;}

"False"     {yylval.key = strdup(yytext); return FALSE;}

"="         { yylval.op = strdup(yytext); return EQ;}
"+="        { yylval.op = strdup(yytext); return AEQ;}
"-="        { yylval.op = strdup(yytext); return SEQ; }
"//="       { yylval.op = strdup(yytext); return FDEQ; }
"**="       { yylval.op = strdup(yytext); return EEQ; }
"*="        { yylval.op = strdup(yytext); return MEQ;}
"/="        { yylval.op = strdup(yytext); return DIEQ;}
"%="        { yylval.op = strdup(yytext); return MOEQ;}
">>="       { yylval.op = strdup(yytext); return BREQ; }
"<<="       { yylval.op = strdup(yytext); return BLEQ; }

"+"         { yylval.op = strdup(yytext); return PLUS;}
"**"        { yylval.op = strdup(yytext); return EXP; }
"*"         { yylval.op = strdup(yytext); return MUL;}
"//"        { yylval.op = strdup(yytext); return FDIV; }
"/"         { yylval.op = strdup(yytext); return DIV;}
"%"         { yylval.op = strdup(yytext); return MOD;}
"-"         { yylval.op = strdup(yytext); return MINUS; }

"and"       {yylval.op = strdup(yytext); return AND;}
"or"        {yylval.op = strdup(yytext); return OR;}
"not"       {yylval.op = strdup(yytext); return NOT;}

"in"        {yylval.op = strdup(yytext); return IN;}
"not in"    {yylval.op = strdup(yytext); return NIN;}

"is"        {yylval.op = strdup(yytext); return IS;}
"is not"    {yylval.op = strdup(yytext); return ISN;}

">"         {yylval.op = strdup(yytext); return GT;}
"<"         {yylval.op = strdup(yytext); return LT;}
">="        {yylval.op = strdup(yytext); return GTE;}
"<="        {yylval.op = strdup(yytext); return LTE;}
"=="        {yylval.op = strdup(yytext); return DEQ;}
"!="        {yylval.op = strdup(yytext); return NE;}

"&"         {yylval.op = strdup(yytext); return BAND;}
"~"         {yylval.op = strdup(yytext); return BNOT;}
"|"         {yylval.op = strdup(yytext); return BOR;}
"^"         {yylval.op = strdup(yytext); return BXOR;}
">>"        {yylval.op = strdup(yytext); return RSHIFT;}
"<<"        {yylval.op = strdup(yytext); return LSHIFT;}

{INT}       {int a = installLit(yytext,"INT"); yylval.value = strdup(yytext); return INT;}
{str}       {int a = installLit(yytext,"STR"); yylval.value = strdup(yytext); return LITERAL;}
{FLOAT}     {int a = installLit(yytext,"FLOAT"); yylval.value = strdup(yytext); return FLOAT;}

{list}      {int a = installID(yytext, "LIST"); yylval.lexeme = strdup(yytext); return LIST; }
{tuple}     {int a = installID(yytext, "TUPLE"); yylval.lexeme = strdup(yytext); return TUPLE; }
{set}       {int a = installID(yytext, "SET"); yylval.lexeme = strdup(yytext); return SET; }
{dict}      {int a = installID(yytext, "DICT"); yylval.lexeme = strdup(yytext); return DICT; }

{id}        {int a = installID(yytext, "ID"); yylval.lexeme = strdup(yytext); return id; }

":"         {yylval.delim = strdup(yytext); return COLON;}
"\t"        {yylval.delim = strdup(yytext); return SPACE;}
"    "      {yylval.delim = strdup(yytext); return SPACE;}
"\n"        {yylval.delim = strdup(yytext); return NL;}
"("         {yylval.delim = strdup(yytext); return "(";}
")"         {yylval.delim = strdup(yytext); return ")";}

<<EOF>>     {saveST(); return 0;}

%%

int yywrap(){
  return 1;
}
