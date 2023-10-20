#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

char	*get_file_contents(const char *filename) {
	FILE	*file = fopen(filename, "rb");
	if (!file)
	{
		fprintf(stderr, "Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	long	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char	*contents = calloc(file_size + 1, 1);
	if (!contents)
	{
		fprintf(stderr, "Memory allocation failled\n");
		exit(EXIT_FAILURE);
	}
	fread(contents, 1, file_size, file);
	contents[file_size] = '\0';
	fclose(file);

	return(contents);
}

