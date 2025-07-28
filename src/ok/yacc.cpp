#define SCANNER_HEADER
#define PARSER_HEADER
#include "pch.h"
#include <cstdio>
int main(int argc, const char *argv[])
{
	void *scanner;
	for (size_t i = 1; argv[i]; i++)
	{
		FILE *f = fopen(argv[i], "rb");
		if (!f) {
			fprintf(stderr, "Failed to open file: %s\n", argv[i]);
			continue;
		}
		yylex_init(&scanner);
		yyset_in(f, scanner);
		yy::parser parser(scanner);
		try {
			parser();
		} catch (const std::exception& ex) {
			fprintf(stderr, "Parsing failed for file: %s\nError: %s\n", argv[i], ex.what());
		}
		yylex_destroy(scanner);
		fclose(f);
	}
	return 0;
}
