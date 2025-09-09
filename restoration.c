#include "readaline.h"
#include "restoration.h"


void restoration(FILE *fp) 
{
        char *datapp;

        /*
        int i = readaline(fp, &datapp);

        for (int j = 0; j < i; j++) {
                printf("%c", datapp[j]);
        }
        printf("\n");

        (void) i;
        
        */

        /*Declare the instances of Hanson's ADTs*/
        
        Table_T injectedTable = Table_new (1000, NULL, NULL);
        assert(injectedTable != NULL);
        

        Seq_T originalWords = Seq_new(1000);
        assert(injectedTable != NULL);

        //TODO: check for null charcters working
        while (datapp != NULL) {
                size_t lineSize = readaline(fp, &datapp);
                
                check(&datapp, lineSize);
        }

        
        //while fp is not end of file / null however we deicde
                //call readaline
                //string seperating (non-digits from digits)

                //create atom with non-digits,
                


        free(datapp);
        return;
}


// ? do we want to make this in a different .h file?



void check(char **datapp, size_t length, 
           Seq_T *originalWords, Table_T *injectedTable) {


        two pointers here that hodl teh dirt and lineCleaning

        null Atom
        line cleaning cleans both and updates the pointers 

        atom
        c-string

        linecleaning -- updates the atom and c-string to have the curr line's dirty and clean'

        void 
        
        if 

        
        //check if atom exists in table as a key
                        //if so and the sequence has been started, add non-digit cstring to sequence

                        //if so and seq has not been started, put what is currently in table as first element,
                        //add what was just found as second element

                        //if not, make key value pair with atom and cstring and add to table

        
        

}

// ? maybe single deref?
char *lineCleaning(char **datapp, size_t length) {
        //split into clean and dirty
        //update atom with dirty local c-string that we make 


        //make cstring with clean
        //
}
