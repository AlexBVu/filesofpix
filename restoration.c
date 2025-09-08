#include "readaline.h"
#include "restoration.h"

void restoration(FILE *fp) 
{


        printf("Hello this is in restoration!\n");

        char *datapp;

        int i = readaline(fp, &datapp);

        for (int j = 0; j < i; j++) {
                printf("%c", datapp[j]);
        }
        printf("\n");

        (void) i;
        free(datapp);
        return;
}