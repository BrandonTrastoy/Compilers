%{
#include <stdlib.h>
#include "parse.tab.h"
#define YY_SKIP_YYWRAP
%}

%%
"F"     	{ yylval = 0; return BOOL; }
"T"     	{ yylval = 1; return BOOL; }
"&&"  		{ return AND; }
"||"  		{ return OR; }
"^"    		{ return XOR; }
"~"			{ return NOT; }
"("       	return *yytext;
")"       	return *yytext;
[ \t]    	; 
.       	{ return yytext[0]; }
%%

int yywrap() { 
	return 1; 
}
