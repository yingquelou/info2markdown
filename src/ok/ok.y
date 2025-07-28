%require "3.0"
%language "c++"
%define api.token.constructor
%define api.value.type variant
%{
#define SCANNER_HEADER
#include"pch.h"
%}

%param {void* yyscanner}
/*
With both ‘%define api.value.type variant’ and ‘%define
api.token.constructor’, the parser defines the type ‘symbol_type’, and
expects ‘yylex’ to have the following prototype.

 -- Function: parser::symbol_type yylex ()
 -- Function: parser::symbol_type yylex (TYPE1 ARG1, ...)
     Return a _complete_ symbol, aggregating its type (i.e., the
     traditional value returned by ‘yylex’), its semantic value, and
     possibly its location.  Invocations of ‘%lex-param {TYPE1 ARG1}’
     yield additional arguments.
*/
/*
%code [requires|provides|top]
Code output location
- requires

    - The parser header file and the parser implementation file 
      before the Bison-generated definitions of the value and 
      location types (‘YYSTYPE’ and ‘YYLTYPE’ in C).

- provides

    - The parser header file and the parser implementation file 
      after the Bison-generated value and location types (‘YYSTYPE’ 
      and ‘YYLTYPE’ in C), and token definitions.

- top

    - Near the top of the parser implementation file.
*/
%code provides{
extern YY_DECL;
}

%token <long double> number

%%
start:
|number start{
std::cout<<"number:\t"<<$1<<'\n';
}
;

%%
void yy::parser::error(const std::string&msg){
    throw msg;
}