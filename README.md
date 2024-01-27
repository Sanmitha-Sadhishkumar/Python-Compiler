# Python-Compiler
A compiler for Python language using lex, yacc, etc

#To Run (Directories mentioned): 

Inside lex dir:
flex tokens.l             # Generates lex.yy.c

Inside yacc dir:
bison -d -v expressions.y      # Generates expressions.tab.c and expressions.tab.h

gcc expressions.tab.c ../lex/lex.yy.c ../C_routines/SyntaxTree.c ../C_routines/SymbolTable.c ../C_routines/3AddrCode.c ../C_routines/CodeOptim.c -o myprg && myprg