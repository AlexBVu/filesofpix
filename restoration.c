#include "restoration.h"


Except_T restoException = { NULL };

void restoration(FILE *fp) 
{
        char *datapp;
        bool originalLinesFound = false;

        Table_T injectedTable = Table_new (1000, NULL, NULL);
        
        Seq_T originalWordsSeq = Seq_new(1000);

        if (injectedTable == NULL || originalWordsSeq == NULL) {
                RAISE(restoException);
        }

        size_t lineSize = readaline(fp, &datapp);

        while (datapp != NULL) {
                check(&datapp, lineSize, &originalWordsSeq,
                      &injectedTable, &originalLinesFound);
                free(datapp);
                lineSize = readaline(fp, &datapp);
        }
        printState(&originalWordsSeq);
        
        for (int i = 0; i < Seq_length(originalWordsSeq); i++) {
                free(Seq_get(originalWordsSeq, i));
        }
        Table_map(injectedTable, freeTableContents, NULL);
        Table_free(&injectedTable);
        Seq_free(&originalWordsSeq);

        
        return;
}

// ? can our table only hold num instances and not the whole line?


void check(char **datapp, size_t lineSize, 
           Seq_T *originalWords, Table_T *injectedTable, bool *seqFound) 
{
        char *cleanedLine = (char *)malloc(1000 * sizeof(*cleanedLine));
        assert(cleanedLine != NULL);
        const char *str_atom = lineCleaning(datapp, lineSize, cleanedLine);
        
        if (Table_get(*injectedTable, str_atom) == NULL) {
                if (!(*seqFound)) {
                        Table_put(*injectedTable, str_atom, cleanedLine);
                } else {
                        free(cleanedLine);
                        cleanedLine = NULL;
                }
                
        } else {
                if (!(*seqFound)) {
                        *seqFound = true;
                        char *firstLine = Table_get(*injectedTable, str_atom);

                        char *firstLineCopy = malloc(strlen(firstLine) + 1);
                        assert(firstLineCopy != NULL);
                        strcpy(firstLineCopy, firstLine);

                        Seq_addhi(*originalWords, firstLineCopy);

                }      
                Seq_addhi(*originalWords, cleanedLine);
        }
}



                                
const char *lineCleaning(char **datapp, size_t length, char *cleanedLine) 
{
        char *dirtyCString = (char *)malloc(1000 * sizeof(*dirtyCString));
        assert(dirtyCString != NULL);

        size_t cleanedIndex = 0, dirtyIndex = 0;
        bool inNumber = false;

        for (size_t i = 0; i < length; i++) {
                char currChar = (*datapp)[i];
                if (currChar >= '0' && currChar <= '9') {
                        cleanedLine[cleanedIndex++] = currChar;
                        inNumber = true;
                } else {
                        dirtyCString[dirtyIndex++] = currChar;
                        if (inNumber) {
                                cleanedLine[cleanedIndex++] = ' ';
                                inNumber = false;
                        }
                }
        }
        if (cleanedIndex > 0 && cleanedLine[cleanedIndex - 1] == ' ') {
                cleanedIndex--;
        }
        const char *dirtyAtom = Atom_new(dirtyCString, dirtyIndex);
        cleanedLine[cleanedIndex] = '\0';

        free(dirtyCString);
        dirtyCString = NULL;

        return dirtyAtom;
}

size_t countWidth(Seq_T *originalWords) {
        char *firstLine = Seq_get(*originalWords, 0);
        size_t width = 0;
        size_t i = 0;
        
        while (firstLine[i] != '\0') {
                /* Skip whitespace */
                while (firstLine[i] == ' ' && firstLine[i] != '\0') {
                        i++;
                }
                if (firstLine[i] >= '0' && firstLine[i] <= '9') {
                        width++;
                        /* Skip the rest of this number */
                        while (firstLine[i] >= '0' && firstLine[i] <= '9' && firstLine[i] != '\0') {
                                i++;
                        }
                } else if (firstLine[i] != '\0') {
                        i++;
                }
        }

        return width;
}

void printState(Seq_T *originalWords) 
{

        size_t width = countWidth(originalWords);
        size_t height = Seq_length(*originalWords);
        
        printf("P5\n%zu %zu\n255\n", width, height);
        
        for (size_t row = 0; row < height; row++) {
                char *currLine = Seq_get(*originalWords, row);
                size_t i = 0;
                while (currLine[i] != '\0') {
                        while (currLine[i] == ' ' && currLine[i] != '\0') {
                                i++;
                        }
                        if (currLine[i] >= '0' && currLine[i] <= '9') {
                                int pixelValue = 0;
                                while (currLine[i] >= '0' && currLine[i] <= '9'
                                       && currLine[i] != '\0') {
                                        pixelValue = pixelValue * 10 + (currLine[i] - '0');
                                        i++;
                                }
                                putchar((unsigned char)pixelValue);
                        } else if (currLine[i] != '\0') {
                                i++;
                        }
                }
        }
}

void freeTableContents(const void *key, void **value, void *cl) {
        (void) cl;
        (void) key;
        free(*value);
        *value = NULL;
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