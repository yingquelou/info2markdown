/*
利用词法分析器对info <topic> --subnodes -o <file>命令生成的文档进行转换,转换为其他格式(例如：markdown,html,rst等)
*/
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
#include <regex>
#include <map>
#include <string>
std::map<std::string, std::string> parseLine(const std::string &line) {
    static std::regex pattern(R"((\w+):\s*([^,]+))");
	std::map<std::string, std::string> result;
    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        result[it->str(1)] = it->str(2);
    }
    return result;
}
std::string replaceSpacesWithHyphens(const std::string& str) {
	std::string result = str;
	std::replace(result.begin(), result.end(), ' ', '-');
	return result;
}
std::string extractConceptIndex(const std::string& line) {
	static std::regex re(R"(\*\s*([Nn]ote\s*)?([^:\*\n]+)::)");
	std::smatch match;
	if (std::regex_search(line, match, re) && match.size() > 2) {
		return match.str(2);
	}
	return "";
}
%}
/*
*/
digit [[:digit:]]
space [[:space:]]
cntrl [[:cntrl:]]
alpha [[:alpha:]]
alnum [[:alnum:]]
number [+-]?{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?
entry {alnum}+:[^,\n]+


%%

%{
	// rules节第一个Action之前的所有%{...}%块,将按出现顺序逐字追加到扫描器函数体初始化区域的末尾
%}

^{entry}(,{space}*{entry})* {
std::string line(yytext,yytext+yyleng);
std::map<std::string, std::string> parsed = parseLine(line);
fprintf(yyout, "# %s\n", parsed["Node"].c_str());
}

\*{space}*[^:\*\n]*:: {
	std::string content=extractConceptIndex(std::string(yytext, yytext + yyleng));
	if (!content.empty()) {
		fprintf(yyout, "[%s](#%s)", content.c_str(), replaceSpacesWithHyphens(content).c_str());
	}
}

%%
