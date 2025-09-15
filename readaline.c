
#include <stdlib.h>
#include <stdio.h>
#include "readaline.h"
#include <except.h>
#include <assert.h>

Except_T readaline_except = { NULL };

size_t readaline(FILE *inputfd, char **datapp) 
{
        if (inputfd == NULL || datapp == NULL) {
                RAISE(readaline_except);
        }
        char *lineString = (char *)malloc(1000 * sizeof(*lineString));
        assert(lineString != NULL);
	size_t i = 0;
        char curr = fgetc(inputfd);

	while (curr != '\n' && curr != EOF) {
                lineString[i++] = curr;
                curr = fgetc(inputfd);
                if (i > 999) {
                        fprintf(stderr, "readaline: input line too long\n");
                        exit(4);
                }
	}

        if (i == 0 && curr == EOF) {
                free(lineString);
                *datapp = NULL;
                return 0;
        } else {
                lineString[i] = '\0';
                *datapp = lineString;
                return i;
        }
}