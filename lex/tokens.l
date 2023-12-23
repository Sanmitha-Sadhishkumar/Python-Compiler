%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct SymbolTable{
  char token[10];
  char attr[100];
}SymbolTable;

SymbolTable ST[1000];
int STn=0;

void printST(){
  printf("\nPrinting Symbol Table ");
  for(int i=0;i<STn;i++){
    printf("\n%s : %s",ST[i].token, ST[i].attr);
  }
}

int installID(char *a){
  for(int i=0;i<STn;i++){
    if((strcmp(ST[i].token, "ID")==0)&&(strcmp(ST[i].attr, a)==0)){
      return i;
    }
  }
  strcpy(ST[STn].token,"ID");
  strcpy(ST[STn].attr,a);
  STn++;
  return STn-1;
}

int installNum(char *b){
  for(int i=0;i<STn;i++){
    if((strcmp(ST[i].token, "NUM")==0)&&(strcmp(ST[i].attr, b)==0)){
      return i;
    }
  }
  strcpy(ST[STn].token,"NUM");
  strcpy(ST[STn].attr,b);
  STn++;
  return STn-1;
}

%}

id [a-zA-Z_][a-zA-Z_0-9]*

class "class"
from "from"
None "None"
continue "continue"
global "global"
pass "pass"
def "def"
if "if"
raise "raise"
del "del"
import "import"
return "return"
as "as"
elif "elif"
try "try"
assert "assert"
else "else"
while "while"
async "async"
except "except"
lambda "lambda"
with "with"
await "await"
finally "finally"
nonlocal "nonlocal"
yield "yield"
break "break"
for "for"

delimiter (" "|"\t"|"\n")+

relop >|<|<=|>=|==|!=
assign =|"+="|"-="|"*="|"**="|"%="|"/="|"//="|"&="|"<<="|">>="|"^="
arith "+"|"-"|"*"|"**"|"%"|"/"|"//"
logical "and"|"or"|"not"
bitwise "&"|"^"|"~"|"|"|">>"|"<<"
idop "is"
memop "in"

int [-+]?[0-9]+
float [-+]?[0-9]+([.][0-9]+)?([Ee][+-]?[0-9]+)?
bool (True|False)
str (\"([^\"\\\\]|\\\\.)*\")|('([^'\\\\]|\\\\.)*')


%%
{class} {printf("keyword ");}
{from} {printf("keyword ");}
{None} {printf("keyword ");}
{continue} {printf("keyword ");}
{global} {printf("keyword ");}
{pass} {printf("keyword ");}
{def} {printf("keyword ");}
{if} {printf("keyword ");}
{raise} {printf("keyword ");}
{del} {printf("keyword ");}
{import} {printf("keyword ");}
{return} {printf("keyword ");}
{as} {printf("keyword ");}
{elif} {printf("keyword ");}
{try} {printf("keyword ");}
{assert} {printf("keyword ");}
{else} {printf("keyword ");}
{while} {printf("keyword ");}
{async} {printf("keyword ");}
{except} {printf("keyword ");}
{lambda} {printf("keyword ");}
{with} {printf("keyword ");}
{await} {printf("keyword ");}
{finally} {printf("keyword ");}
{nonlocal} {printf("keyword ");}
{yield} {printf("keyword ");}
{break} {printf("keyword ");}
{for} {printf("keyword ");}

{int} {printf("\nInteger : %s ",yytext);
      int a = installNum(yytext);
      printST();}

{str} {printf("String ");}
{float} {printf("Float ");}
{bool} {printf("Boolean ");}

{relop} {printf("relop ");}
{assign} {printf("assign ");}
{arith} {printf("arith ");}
{logical} {printf("logical ");}
{bitwise} {printf("bitwise ");}
{idop} {printf("idop ");}
{memop} {printf("memop");}

{id} {printf("\nIdentifier : %s ",yytext);
      int a = installID(yytext);
      printST();}
%%

void main(){
    yylex();
}

int yywrap() { 
  return 1; 
} 