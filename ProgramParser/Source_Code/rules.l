/****************************************************************************************************************
  Name: Bryan Johnson             NetID: btj117
  Course: CSE 4714              Assignment: Part 2
  Programming Environment: Visual Studio Code
  Purpose of File: Contains lex rules for parsing tokens in part 2.
****************************************************************************************************************/
%option yylineno
%option noyywrap
%{
#include "lexer.h"

%}

%%

 /* Ignore whitespace */

[ \n\t\r]+               /* nop */

 /* finds BEGIN */
BEGIN {return TOK_BEGIN;}

 /* finds BREAK */
BREAK {return TOK_BREAK;}

 /* finds CONTINUE */
CONTINUE {return TOK_CONTINUE;}
 
 /* finds DOWNTO */
DOWNTO {return TOK_DOWNTO;}

 /* finds ELSE */
ELSE {return TOK_ELSE;}

 /* finds END */
END {return TOK_END;}

 /* finds FOR */
FOR {return TOK_FOR;}

 /* finds IF */
IF {return TOK_IF;}

 /* finds LET */
LET {return TOK_LET;}

 /* finds PROGRAM */
PROGRAM {return TOK_PROGRAM;}

 /* finds READ */
READ {return TOK_READ;}

 /* finds THEN */
THEN {return TOK_THEN;}

 /* finds TO */
TO {return TOK_TO;}

 /* finds VAR */
VAR {return TOK_VAR;}

 /* finds WHILE */
WHILE {return TOK_WHILE;}

 /* finds WRITE */
WRITE {return TOK_WRITE;}

 /* finds INTEGER */
INTEGER {return TOK_INTEGER;}

 /* finds REAL */
REAL {return TOK_REAL;}

 /* finds ; */
; {return TOK_SEMICOLON;}

 /* finds : */
: {return TOK_COLON;}

 /* finds ( */
\( {return TOK_OPENPAREN;}

 /* finds ) */
\) {return TOK_CLOSEPAREN;}

 /* finds { */
\{ {return TOK_OPENBRACE;}

 /* finds } */
\} {return TOK_CLOSEBRACE;}

 /* finds + */
\+ {return TOK_PLUS;}

 /* finds - */
\- {return TOK_MINUS;}

 /* finds * */
\* {return TOK_MULTIPLY;}

 /* finds / */
\/ {return TOK_DIVIDE;}

 /* finds := */
\:\= {return TOK_ASSIGN;}

 /* finds = */
\= {return TOK_EQUALTO;}

 /* finds < */
\< {return TOK_LESSTHAN;}

 /* finds > */
\> {return TOK_GREATERTHAN;}

 /* finds <> */
\<\> {return TOK_NOTEQUALTO;}

 /* finds MOD */
MOD {return TOK_MOD;}

 /* finds NOT */
NOT {return TOK_NOT;}

 /* finds OR */
OR {return TOK_OR;}
 
 /* finds AND */
AND {return TOK_AND;}

 /* finds string literal */
\'(\\.|[^'\\\n])*\' { if (strlen(yytext) <= 80) {return TOK_STRINGLIT;} else {return TOK_UNKNOWN;}}

 /* finds interger literal */
[0-9]* {return TOK_INTLIT;}

 /* finds float literal */
[0-9]+\.[0-9]+ {return TOK_FLOATLIT;}

 /* finds identifier of character length 8 */
[A-Z][A-Z0-9]+|[A-Z] {if (strlen(yytext) <= 8) {return TOK_IDENT;} else {return TOK_UNKNOWN;}}

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }
