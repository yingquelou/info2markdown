#define SCANNER_HEADER
#define PARSER_HEADER
#include "pch.h"
#include "utils.h"
#include <cstdio>
#include <regex>
#include <fstream>
int main(int argc, const char *argv[])
{
	void *scanner;
	FILE *f, *out;
	for (size_t i = 1; argv[i]; i++)
	{
		std::vector<std::string> nodes;
		{
			std::ifstream ifs(argv[i]);
			nodes = utils::collectNodeLines(ifs);
		}
		auto maps = utils::getNodeLevels(nodes);
		f = fopen(argv[i], "rb");
		if (!f)
		{
			fprintf(stderr, "Failed to open file: %s\n", argv[i]);
			continue;
		}
		std::string outname = std::string(argv[i]) + ".md";
		out = fopen(outname.c_str(), "wb");
		if (!out)
		{
			fprintf(stderr, "Failed to open output file: %s\n", outname.c_str());
			fclose(f);
			continue;
		}
		yylex_init_extra(&maps, &scanner);
		yyset_out(out, scanner);
		yyset_in(f, scanner);
		try
		{
			yylex(scanner);
		}
		catch (const std::exception &ex)
		{
			fprintf(stderr, "Parsing failed for file: %s\nError: %s\n", argv[i], ex.what());
		}
		yylex_destroy(scanner);
		fclose(f);
	}

	return 0;
}
/*
File: flex.info,  Node: Performance,  Next: Cxx,  Prev: Scanner Options,  Up: Top
识别一系列以上形式的键值对,构建为一个或多个树
其中Node是某个树节点,Up是上级节点
 */
