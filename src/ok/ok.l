%option nounistd noyywrap stack reentrant
%top {
/*
	definitions节的所有top块将按出现顺序逐字追加到扫描器实现文件的顶部
	需要头文件的话,也会输出到扫描器头文件顶部
*/
}
%{
/*
	definitions节的所有%{...}%块将按出现顺序逐字追加到扫描器实现文件的特定的区域
	此时flex仅为我们完成了部分的定义或声明(宏、类型、变量、函数)
*/
#define PARSER_HEADER
#include"pch.h"
#include <sstream>
template <typename T>
T As(const std::string &s)
{
	T t;
	std::istringstream is(s);
	is >> t;
	return t;
}
%}
digit [[:digit:]]
space [[:space:]]
cntrl [[:cntrl:]]
number [+-]?{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?

%%

%{
	// rules节第一个Action之前的所有%{...}%块,将按出现顺序逐字追加到扫描器函数体初始化区域的末尾
%}

{number} {
 return {yy::parser::token_type::number,As<long double>({yytext,yytext+yyleng})};
}

%%
