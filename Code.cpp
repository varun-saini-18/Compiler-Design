/* Definition section */
%{
#include <stdio.h> #include
<stdlib.h> int line_number = 0;
int cmt_number = 0;
%}
/* Definition of regular expression label */
letter [a-zA-Z] digit [0-9]
id {letter}+({letter}|{digit})* number {digit}+
float_number {digit}+[\.]+{number}
%x C_Comment
%x Str
/* Rules section */
%%
"/*" {BEGIN(C_Comment);printf("%s", yytext);++cmt_number;}
<C_Comment>\n {++cmt_number;++line_number;printf("\n");}
<C_Comment>"*/" { BEGIN(INITIAL);printf("%s \t C Comment\n", yytext); }
<C_Comment>.
{
printf("%s", yytext);
}
"\"" { BEGIN(Str);printf("%s \t QUOTA\n", yytext); }
<Str>"\"" { BEGIN(INITIAL);printf("%s \t QUOTA\n", yytext); }
<Str>([^\\\"]|\\.)+ {printf("%s \t STR_CONST\n", yytext); }
"//".* { ++cmt_number;printf("%s \t C++ Comment\n", yytext); }
"+" { printf("%s \t ADD\n", yytext);}
"-" { printf("%s \t SUB\n", yytext);}
"*" { printf("%s \t MUL\n", yytext);}
"/" { printf("%s \t DIV\n", yytext);}
"%" { printf("%s \t MOD\n", yytext);}
"++" { printf("%s \t INC\n", yytext);}
"--" { printf("%s \t DEC\n", yytext);}
"--" { printf("%s \t DEC\n", yytext);}
">" { printf("%s \t MT\n", yytext);}
"<" { printf("%s \t LT\n", yytext);}
">=" { printf("%s \t MTE\n", yytext);}
"<=" { printf("%s \t LTE\n", yytext);}
"==" { printf("%s \t EQ\n", yytext);}
"!=" {printf("%s \tNE\n", yytext);}
"[" {printf("%s\tLSB\n",yytext);}
"]" { printf("%s \t RSB\n", yytext); }
"," { printf("%s \t COMMA\n", yytext); }
";" { printf("%s \tSEMICOLON\n", yytext);}
"print" { printf("%s \t PRINT\n", yytext); }
"if" { printf("%s \t IF\n", yytext);}
"else" { printf("%s \t ELSE\n", yytext); }
"for" { printf("%s \t FOR\n", yytext); }
"while"{ printf("%s \tWHILE\n", yytext);}
"string" { printf("%s \t STRING\n", yytext); }
"int" { printf("%s \t INT\n", yytext); }
"float"{ printf("%s \t FLOAT\n", yytext);}
"=" { printf("%s \t ASGN\n", yytext); }
"+=" { printf("%s \tADDASGN\n", yytext);}
"-=" { printf("%s \t SUBASGN\n", yytext); }
"*=" { printf("%s \t MULASGN\n", yytext); }
"/=" { printf("%s \t DIVASGN\n", yytext); }
"%=" { printf("%s \t MODASGN\n", yytext); }
"&&" { printf("%s \t AND\n", yytext);}
"||" {printf("%s \tOR\n", yytext);}
"!" {printf("%s \tNOT\n", yytext);}
"(" { printf("%s \t LB\n", yytext);}
")" {printf("%s \tRB\n", yytext);}
"{" { printf("%s \t LCB\n", yytext);}
"}" { printf("%s \t RCB\n", yytext); }
"void" {printf("%s \tVOID\n", yytext);}
"bool" { printf("%s \t BOOL\n", yytext); }
"true" { printf("%s \t TRUE\n", yytext); }
"false" { printf("%s \t FALSE\n", yytext);}
"return" {printf("%s \tRET\n", yytext);}
"continue" { printf("%s \t CONT\n", yytext); }
"break" { printf("%s \t BREAK\n", yytext); }
{digit} { printf("%s \t I_CONST\n", yytext); }
{number} { printf("%s \t I_CONST\n", yytext);}
{float_number} { printf("%s \t F_CONST\n", yytext); }
{id} { printf("%s \t ID\n", yytext); }
" " { ; }
\t { ; }
\n {++line_number;}
. {;}// undefined characters
%%
/* C Code section */
int yywrap(void)
{
return 1;
}
int main(int argc,char *argv[])
{
yyin = fopen(argv[1],"r");
yylex();
printf("\nParse over, the line number is %d.\n\n", line_number);
printf("comment: %d lines\n\n", cmt_number);
return 0;
}
