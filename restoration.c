#include "readaline.h"
#include "restoration.h"


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

        
        //TODO: check for null charcters working
        while (datapp != NULL) {

                printf("at the beginning of datapp while loop again\n");
                
                check(&datapp, lineSize, &originalWordsSeq, 
                        &injectedTable, &originalLinesFound);

                /* we must free the line datapp points to*/
                // ! make sure our implementation can handle large files
                // ! we might be freeing incorrectly
                // free(datapp);

                lineSize = readaline(fp, &datapp);
        }



        //  /*cleaned string printing statement*/
        // printf("\ncleanedline is: ");
        // for (size_t i = 0; i < lineSize; i++) {
        //         printf("%c", cleanedLine[i]);
        // }

        // /*dirty string debugging statement*/
        // printf("\ndirty string is: ");
        //         for (size_t i = 0; i < lineSize; i++) {
        //                 printf("%c", str_atom[i]);
        //         }
        //         printf("\n\n");
        
        //if datapp is null do we need to check again?
        
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
        

                   /*
                   check if atom exists in table as a key
                   if so and the sequence has been started, 
                   create & add non-digit cstring to sequence
                   
                   if so and seq has not been started 
                   update seqFound to true
                   
                   if not
                   add atom to table as key and add cstring to table as value
                   
                   */        
                  
                  /*
                  declare clean-cstring
                  declare dirty atom = call linecleaning
                  
                  */
                  
                //
                if (Table_get(*injectedTable, str_atom) != NULL){
                        if (!*seqFound) {
                                *seqFound = true;
                                char *firstLine = Table_get(*injectedTable, str_atom);


                                // ? do we have to cast to void here?
                                Seq_addlo(*originalWords, firstLine);
                                Seq_addlo(*originalWords, cleanedLine);
                                //seq has not been started, add whats in table and what we read in
                        } else {
                                //seq has been started add what we read in 
                                Seq_addlo(*originalWords, cleanedLine);
                        } 

                        //if (seq has not been started)
                        //found original, procceed
                 } else {
                        Table_put(*injectedTable, str_atom, cleanedLine);
                 }
        
        
        
        
        
        
        /* Should be deleted to avoid 31 valgrind errors!!*/

       

                

        /* TEMP voids*/
        (void) originalWords;
        (void) injectedTable;
        (void) seqFound;
        (void) str_atom;


        free(cleanedLine);
        cleanedLine = NULL;

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
        for (i = 0; i < length; i++) {

                //set current character to curr index in datapp
                char currChar = (*datapp)[i];

                /* if current char is a digit */
                if (currChar >= 48 && currChar <= 57) {
                        // printf("\nadding curr char to cleanedLine: %c\n", currChar);
                        cleanedLine[i] = currChar;
                        
                /* if current char is not a digit */
                } else if (currChar < 48 || currChar > 57) {
                        // printf("\nadding curr char to dirtyCString: %c\n", currChar);
                        dirtyCString[i] = currChar;
                }
        }

        
/*
-not dependent on amount of chars in file
-not dependent of if non character is first
-works for the first line
-works with just one
*/
        /*return the atom to be used by check (IN DEBUGGING BEING USED BY RESTO)*/
        /*giving valgrind errors, dependent on lines in .txt file,*/
        const char *dirtyAtom = Atom_new(dirtyCString, i);

        free(dirtyCString);
        dirtyCString = NULL;

        return dirtyAtom;
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

*/