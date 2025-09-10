
#include <stdlib.h>
#include "readaline.h"
#include <assert.h>

size_t readaline(FILE *inputfd, char **datapp) 
{
        char *lineString = (char *)malloc(1000 * sizeof(*lineString));
        
       // TODO: assertions and error handling with bad memory alloc
        assert(lineString != NULL);

	size_t i = 0;

        /*take in the first character*/
        char curr = fgetc(inputfd);


        /*iterate until we reach endline character or if we 
        reach end of file or line capacity*/

	while (curr != '\n' && curr != EOF && i < 999) {

                lineString[i++] = curr;
                curr = fgetc(inputfd);
	}

        //SOMETHING LIKE THIS IN PROGRESS
        if (curr == EOF) {
                *datapp = NULL;
                return 0;
        } else {
                /*set end of our cstring to null character to validate it*/
                lineString[i] = '\0';
                *datapp = lineString;

                return i;
        }


        
        

}