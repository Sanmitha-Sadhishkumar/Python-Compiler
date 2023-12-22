%{

%}

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

id [a-zA-Z_][a-zA-Z_0-9]*

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

{int} {printf("Integer ");}
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
{id} {printf("Identifier ");}
%%

void main(){
    yylex();
}

int yywrap() { 
  return 1; 
} 