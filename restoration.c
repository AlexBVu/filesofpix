#include "readaline.h"
#include "restoration.h"


void restoration(FILE *fp) 
{
        char *datapp;

        bool originalLinesFound = false;

        (void) originalLinesFound;

        /*Declare the instances of Hanson's ADTs*/
        
        Table_T injectedTable = Table_new (1000, NULL, NULL);
        assert(injectedTable != NULL);
        


        Seq_T originalWords = Seq_new(1000);
        assert(injectedTable != NULL);

        (void) originalWords;

        /* supposed to be in check() */
        // ! how to malloc a new cleanedline for every line, not just one big one?
        char *cleanedLine = (char *)malloc(1000 * sizeof(*cleanedLine));


        
        //TODO: check for null charcters working
        while (datapp != NULL) {
                size_t lineSize = readaline(fp, &datapp);

                // check(&datapp, lineSize, &originalLinesFound);

                /* is supposed to be in check() */
                const char *str_atom = lineCleaning(&datapp, lineSize, cleanedLine);
               
                printf("\ncleanedLine is: ");
                for (size_t i = 0; i < lineSize; i++) {
                        printf("%c", cleanedLine[i]);
                }
                printf("\n");
                
                (void) str_atom;

        }


        
        //while fp is not end of file / null however we deicde
                //call readaline
                //string seperating (non-digits from digits)

                //create atom with non-digits,


        /* supposed to be in check() */
        free(cleanedLine);

        free(datapp);
        return;
}


// ? do we want to make this in a different .h file?


// ? can our table only hold num instances and not the whole line?
/*

void check(char **datapp, size_t length, 
           Seq_T *originalWords, Table_T *injectedTable, bool *seqFound) 
           {

        
         declare clean-cstring
         declare dirty atom = call linecleaning

        

        check if atom exists in table as a key
                         if so and the sequence has been started, 
                                 create & add non-digit cstring to sequence
                                
                         if so and seq has not been started 
                                 update seqFound to true

                         if not
                                 add atom to table as key and add cstring to table as value
        
                                 
                                 
}
                                
*/

// ? maybe single deref?
// ? do we return a pointer to an atom or no?


const char *lineCleaning(char **datapp, size_t length, char *cleanedLine) 
{

        /*string to hold nondigit characters*/
        char *dirtyCString = (char *)malloc(1000 * sizeof(*dirtyCString));
        
        /*iterate through every character in line*/
        size_t i;
        for (i = 0; i < length; i++) {

                //set current character to curr index in datapp
                char currChar = (*datapp)[i];

                /* if current char is a digit */
                if (currChar >= 48 && currChar <= 57) {
                        printf("\nadding curr char to cleanedLine: %c\n", currChar);
                        cleanedLine[i] = currChar;
                        
                /* if current char is not a digit */
                } else {
                        printf("\nadding curr char to dirtyCString: %c\n", currChar);
                        dirtyCString[i] = currChar;
                }
        }

        /*dirty string debugging statement*/
        printf("\ndirty string is: ");
                for (size_t i = 0; i < length; i++) {
                        printf("%c", dirtyCString[i]);
                }
                printf("\n");

        /*return the atom to be used by check (IN DEBUGGING BEING USED BY RESTO)*/
        const char *dirtyAtom = Atom_new(dirtyCString, i);
        return dirtyAtom;
}
