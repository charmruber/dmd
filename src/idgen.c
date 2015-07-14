#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

struct Msgtable
{
	char *ident;
	char *name;
};

Msgtable msgtable[] =
{
    { "IUnknown" },
    { "Object" },
    { "object" },
    { "max" },
    { "min" },
    { "This", "this" },
    { "ctor", "_ctor" },
    { "dtor", "_dtor" },
    { "classInvariant", "_invariant" },
    { "unitTest", "_unitTest" },
    { "staticCtor", "_staticCtor" },
    { "staticDtor", "_staticDtor" },
    { "init" },
    { "size" },
    { "length" },
    { "offset" },
    { "ModuleInfo" },
    { "ClassInfo" },
    { "classinfo" },
    { "TypeInfo" },
    { "typeinfo" },
    { "withSym", "__withSym" },
    { "result", "__result" },
    { "returnLabel", "__returnLabel" },
    { "delegate" },

    { "nan" },
    { "infinity" },
    { "dig" },
    { "epsilon" },
    { "mant_dig" },
    { "max_10_exp" },
    { "max_exp" },
    { "min_10_exp" },
    { "min_exp" },
    { "re" },
    { "im" },

    { "C" },
    { "D" },
    { "Windows" },
    { "Pascal" },

    { "keys" },
    { "values" },
    { "rehash" },

    { "sort" },
    { "reverse" },
    { "dup" },

    // For inline assembler
    { "__int", "int" },
    { "__dollar", "$" },
    { "__LOCAL_SIZE" },

    // For operator overloads
    { "neg" },
    { "com" },
    { "add" },
    { "sub" },
    { "sub_r" },
    { "mul" },
    { "div" },
    { "div_r" },
    { "mod" },
    { "mod_r" },
    { "eq" },
    { "cmp" },
    { "and" },
    { "or" },
    { "xor" },
    { "shl" },
    { "shl_r" },
    { "shr" },
    { "shr_r" },
    { "ushr" },
    { "ushr_r" },
    { "cat" },
    { "cat_r" },
    { "addass" },
    { "subass" },
    { "mulass" },
    { "divass" },
    { "modass" },
    { "andass" },
    { "orass" },
    { "xorass" },
    { "shlass" },
    { "shrass" },
    { "ushrass" },
    { "catass" },
    { "postinc" },
    { "postdec" },
};


int main()
{
    FILE *fp;
    unsigned i;
#if defined UNICODE
    char L[] = "L";
#else
    char L[] = "";
#endif

    {
	fp = fopen("id.h","w");
	if (!fp)
	{   printf("can't open id.h\n");
	    exit(EXIT_FAILURE);
    }

	fprintf(fp, "// File generated by idgen.c\n");
	fprintf(fp, "#pragma once\n");
	fprintf(fp, "#ifndef ID_H\n");
	fprintf(fp, "#define ID_H 1\n");
	fprintf(fp, "struct Identifier;\n");
	fprintf(fp, "struct Id\n");
	fprintf(fp, "{\n");

	for (i = 0; i < sizeof(msgtable) / sizeof(msgtable[0]); i++)
	{   char *id = msgtable[i].ident;

	    fprintf(fp,"    static Identifier *%s;\n", id);
	}

	fprintf(fp, "    static void initialize();\n");
	fprintf(fp, "};\n");
	fprintf(fp, "#endif\n");

	fclose(fp);
    }

    {
	fp = fopen("id.c","w");
	if (!fp)
	{   printf("can't open id.c\n");
	    exit(EXIT_FAILURE);
	}

	fprintf(fp, "// File generated by idgen.c\n");
	fprintf(fp, "#include \"id.h\"\n");
	fprintf(fp, "#include \"identifier.h\"\n");

	for (i = 0; i < sizeof(msgtable) / sizeof(msgtable[0]); i++)
	{   char *id = msgtable[i].ident;
	    char *p = msgtable[i].name;

	    if (!p)
		p = id;
	    fprintf(fp,"Identifier *Id::%s;\n", id);
	}

	fprintf(fp, "void Id::initialize()\n");
	fprintf(fp, "{\n");

	for (i = 0; i < sizeof(msgtable) / sizeof(msgtable[0]); i++)
	{   char *id = msgtable[i].ident;
	    char *p = msgtable[i].name;

	    if (!p)
		p = id;
	    fprintf(fp,"    %s = Lexer::idPool(\"%s\");\n", id, p);
	}

	fprintf(fp, "}\n");

	fclose(fp);
    }

    return EXIT_SUCCESS;
}
