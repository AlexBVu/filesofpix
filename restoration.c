#include "readaline.h"
#include "restoration.h"
#include <string.h>


void restoration(FILE *fp) 
{
        char *datapp;
        bool originalLinesFound = false;

        /*Declare the instances of Hanson's ADTs*/
        Table_T injectedTable = Table_new (1000, NULL, NULL);
        assert(injectedTable != NULL);
        
        Seq_T originalWordsSeq = Seq_new(1000);
        assert(injectedTable != NULL);

        /* could we call readaline here? */
        size_t lineSize = readaline(fp, &datapp);
        


        // ? gridWith & widthChecked have been implemented in restoration, but not at all in check or linecleaning
        //TODO: check for null charcters working
        while (datapp != NULL) {
                check(&datapp, lineSize, &originalWordsSeq,
                      &injectedTable, &originalLinesFound);


                /* we must free the line datapp points to*/
                // ! make sure our implementation can handle large files
                // ! we might be freeing incorrectly
                // free(datapp);

                lineSize = readaline(fp, &datapp);
        }

        //if datapp is null do we need to check again?
        printState(&originalWordsSeq);
        
        /*frees the table and seq*/
        Table_free(&injectedTable);
        Seq_free(&originalWordsSeq);

        /*frees datapp*/
        free(datapp);
        datapp = NULL;


        return;
}

// ? can our table only hold num instances and not the whole line?


void check(char **datapp, size_t lineSize, 
           Seq_T *originalWords, Table_T *injectedTable, bool *seqFound) 
{
                 
        char *cleanedLine = (char *)malloc(1000 * sizeof(*cleanedLine));
        assert(cleanedLine != NULL);
        
        const char *str_atom = lineCleaning(datapp, lineSize, cleanedLine);
        
        // printf("cleaned line: ");
        // for(size_t i = 0; i < lineSize; i++) {
        //         printf("%c", cleanedLine[i]);
        // }
        // printf("\n");
        
        if (Table_get(*injectedTable, str_atom) == NULL) {
                if (!(*seqFound)) {
                        /*
                        testing
                        printf("dirtyAtom doesn't exist, putting into table\n\n");
                        */
                        Table_put(*injectedTable, str_atom, cleanedLine);
                }
                
        } else {
                if (!(*seqFound)) {
                        /*
                        testing
                        printf("dirtyAtom already exists, seq hasn't been started\n");
                        */
                        *seqFound = true;
                        char *firstLine = Table_get(*injectedTable, str_atom);


                        // ? do we have to cast to void here?
                        Seq_addhi(*originalWords, firstLine);
                        //seq has not been started, add whats in table and what we read in
                }      
                
                        //seq has been started add what we read in 
                        Seq_addhi(*originalWords, cleanedLine);

                        /*
                        testing
                        printf("cleanedLine being added to seq\n\n");

                        */
                
        }
        /* remove this but do it somewhere
        free(cleanedLine);
        cleanedLine = NULL;
        */

        /* atom's will be in still reachable */
                                 
}



                                
const char *lineCleaning(char **datapp, size_t length, char *cleanedLine) 
{

        // !dirtyCString is sometimes unitialized, and when we use it, it doesn't work

        /*string to hold nondigit characters*/
        char *dirtyCString = (char *)malloc(1000 * sizeof(*dirtyCString));
        assert(dirtyCString != NULL);

        // ! when first char in line is non-digit, our code incorrectly adds one index to cleanedLine
        /*iterate through every character in line*/
        size_t i;
        size_t cleanedIndex = 0;
        size_t dirtyIndex = 0;
        bool inNumber = false;


        for (i = 0; i < length; i++) {

                //set current character to curr index in datapp
                char currChar = (*datapp)[i];

                /* if current char is a digit */
                if (currChar >= 48 && currChar <= 57) {
                        // printf("\nadding curr char to cleanedLine:%c-\n", currChar);
                        cleanedLine[cleanedIndex++] = currChar;
                        inNumber = true;
                        
                /* if current char is not a digit */
                } else if (currChar < 48 || currChar > 57) {
                        // printf("\nadding curr char to dirtyCString:%c-\n", currChar);
                        dirtyCString[dirtyIndex++] = currChar;
                        cleanedLine[cleanedIndex++] = ' ';
                        inNumber = false;
                }

        }

        if (cleanedIndex > 0 && cleanedLine[cleanedIndex - 1] == ' ') {
                cleanedIndex--;
        }

       
        /*return the atom to be used by check (IN DEBUGGING BEING USED BY RESTO)*/
        /*giving valgrind errors, dependent on lines in .txt file,*/
        const char *dirtyAtom = Atom_new(dirtyCString, dirtyIndex);

        // ?maybe we do digitCount + 1?
        cleanedLine[cleanedIndex] = '\0';

        free(dirtyCString);
        dirtyCString = NULL;

        return dirtyAtom;
}

size_t countWidth(Seq_T *originalWords) {
        char *firstLine = Seq_get(*originalWords, 0);
                char curr = firstLine[0];
                size_t count = 0;

                while (curr != '\0') {
                        // printf("%zu\n", count);
                        curr = firstLine[count];
                        count++;
                }
        // printf("count: %zu\n", count - 1);
        return count - 1;
}

void printState(Seq_T *originalWords) {

        /*variables containing height and width*/
        size_t width = countWidth(originalWords);
        size_t height = Seq_length(*originalWords);
        //printf("height: %zu\n", height);

        
        printf("P5\n%zu %zu\n255", width, height);
        

        //iterate until all rows (lines) have been taken in
        for (size_t row = 0; row < height; row++) {

                /*print newline char for each row and get line*/
                printf("\n");
                char *currLine = Seq_get(*originalWords, row);
                
                /*for every character in every row that isn't null, print*/
                for (size_t column = 0; column < width && currLine[column] != '\0'; column++) {
                        printf("%d", currLine[column]);
                }
        }
        /*print final newline for formatting*/
        printf("\n");


                

}

/*
TODOS:
-error checking
-memory handling
        -map function that can deallocate for everything in table

-
-printing end result
        -handling weird characters

-why can we free things and still point to them after

- Rename variables!

*/