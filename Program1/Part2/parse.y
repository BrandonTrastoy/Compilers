%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(char * s);
%}

%token BOOL AND XOR OR

%start program

%left OR
%left XOR
%left AND
%left '(' ')'
%left NOT

%%
program : expr '.' {
	if($1 > 0)
		printf("T\n");
	else 
		printf("F\n");
	exit(1);
	}
;

expr :   '(' expr ')'			{ $$ = $2; }
	| NOT expr			{ if($2 > 0) {
						$$ = 0;
					} else {
						$$ = 1; 
					} ;}
	| term OR expr		{ $$ = $1 + $3; }
	| term			{ $$ = $1; }
	;
	
term:    factor XOR term	{ if($1 == $3) {
						$$ = 0;
					} else {
						$$ = 1; 
					} ; }
	| factor			{ $$ = $1; }
	;
	
factor : BOOL AND factor 	{ $$ = $1 * $3; }
	| BOOL			{ $$ = $1; }
	;
%%

void yyerror(char* s) {
	fprintf(stderr,"%s\n",s);
}

int main(int argc, char* argv[]) {
	printf("Enter a truth statement: ");
	yyparse();
	return 0;
}


