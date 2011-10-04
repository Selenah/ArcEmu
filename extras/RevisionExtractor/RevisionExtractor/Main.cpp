#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int WriteRevisionHeader(char* filename, int revision, const char* tag);
int main()
{
	printf("Running RevisionExtractor\n");

	int revision = 0;
	std::string tag = "TRUNK";

	FILE* entries = fopen("../.svn/entries", "r");

	if (entries != NULL)
	{
		fseek(entries, 0, SEEK_END);
		auto entriessize = ftell(entries);
		fseek(entries, 0, SEEK_SET);

		char* ent = new char[entriessize];
		fread(ent, 1, entriessize, entries);

		char* dir = strstr(ent, "dir");

		if (dir != NULL)
			revision = atoi(&dir[3]);

		delete[] ent;
		fclose(entries);
	}

	FILE* tags = fopen("../../arcemu-tag", "r");

	if (tags != NULL)
	{
		fseek(tags, 0, SEEK_END);
		auto tagsize = ftell(tags);
		fseek(tags, 0, SEEK_SET);

		char* tagc = new char[tagsize];
		fread(tagc, 1, tagsize, tags);

		std::string tmp = tagc;
		tag = tmp.substr(0, tmp.find("\n"));

		delete[] tagc;
		fclose(tags);
	}


	return WriteRevisionHeader("svn_revision.h", revision, tag.c_str());
}


int WriteRevisionHeader(char* filename, int revision, const char* tag)
{
	FILE* f = fopen(filename, "w");

	if (f == NULL)
	{
		printf("Error: cannot open %s for writing\n", filename);
		return 1;
	}

	fprintf(f, "// This file was automatically generated by the revision extractor.\n// There is no need to modify this file.\n\n");

	fprintf(f, "#ifndef SVN_REVISION_H\n#define SVN_REVISION_H\n\n");
	fprintf(f, "static const char* BUILD_TAG = \"%s\";\n", tag);
	fprintf(f, "static int BUILD_REVISION = %u;\n", revision);

	fprintf(f, "\n\n#endif\n");

	fclose(f);
	return 0;
}