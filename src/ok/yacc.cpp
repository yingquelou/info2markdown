#define SCANNER_HEADER
#define PARSER_HEADER
#include "pch.h"
#include <cstdio>
#include <regex>
int main(int argc, const char *argv[])
{
	void *scanner;
	FILE *f,*out;
	for (size_t i = 1; argv[i]; i++)
	{
		f = fopen(argv[i], "rb");
		if (!f) {
			fprintf(stderr, "Failed to open file: %s\n", argv[i]);
			continue;
		}
		std::string outname = std::string(argv[i]) + ".md";
		out = fopen(outname.c_str(), "wb");
		if (!out) {
			fprintf(stderr, "Failed to open output file: %s\n", outname.c_str());
			fclose(f);
			continue;
		}
		yylex_init(&scanner);
		yyset_out(out, scanner);
		yyset_in(f, scanner);
		try {
			yylex(scanner);
		} catch (const std::exception& ex) {
			fprintf(stderr, "Parsing failed for file: %s\nError: %s\n", argv[i], ex.what());
		}
		yylex_destroy(scanner);
		fclose(f);
	}
	return 0;
}
// 将字符串中的空格替换为-
