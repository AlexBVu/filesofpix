
#include <stdlib.h>
#include "readaline.h"
#include <assert.h>

size_t readaline(FILE *inputfd, char **datapp) 
{
        char *lineString = (char *)malloc(1000 * sizeof(*lineString));
        
       // TODO: assertions and error handling with bad memory alloc
        assert(lineString != NULL);

	size_t i = 0;


        char curr = fgetc(inputfd);

        //load bearing print statement
        // printf("first char%c\n", curr);

	while (curr != '\n' && curr != EOF && i < 999) {
                lineString[i++] = curr;
                curr = fgetc(inputfd);
	}

        lineString[i] = '\0';
        *datapp = lineString;

        return i;

}