#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <sxc_string.h>

enum { INPUT_LINES = 6 };

const char* input[INPUT_LINES] = {
	"Christmas\n",
	"Tuesday\n",
	"Drink more coffee\n",
	"Long sentence, probably forcing a call to realloc\n",
	// Multi-line string, very long..
	"In our experience, C has proven to be a pleasant, expressive, and "
	"versatile language for a wide variety of programs. It is easy to "
	"learn, and it wears well as one's experience with it grows. We hope "
	"that this book will help you to use it well.\n",
	"Kernighan and Ritchie, The C Programming Language\n",
};

const char* prepare_file(const char* path)
{
	FILE* fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "Could not open %s for writing\n", path);
		return NULL;
	}

	for (int i; i < INPUT_LINES; ++i)
		fputs(input[i], fp);

	fclose(fp);
	return path;
}

int main()
{
	const char* path = "/tmp/libsxc_getline_test.txt";	// Linux
	if (!prepare_file(path)) {
		fprintf(stderr, "prepare_file failed with path: %s\n", path);
		return EXIT_FAILURE;
	}

	FILE* fp = fopen(path, "r");
	if (!fp) {
		fprintf(stderr, "Could not open %s for reading\n", path);
		return EXIT_FAILURE;
	}

	String s;
	sxc_string_init(&s);
	for (int i = 0; sxc_getline(fp, &s); sxc_string_clear(&s), ++i) {
		// getline discards '\n' so length should be one shorter
		assert(sxc_string_size(&s) == strlen(input[i]) - 1);

		// the contents should be equal up to the end of read string
		//assert(strncmp(input[i], s.str, s.siz) == 0);
		assert(strncmp(input[i], sxc_string_str(&s),
					sxc_string_size(&s)) == 0);
	}

	sxc_string_free(&s);
	fclose(fp);

	return EXIT_SUCCESS;
}

