#include "readaline.h"
#include "restoration.h"

void restoration(FILE *fp) 
{
        char buff[2];
        int j = 20;
        
        fgets(buff, j, fp);

        printf("-%d-", j);

        for (int i = 0; i < 2; i++) {
                printf("|%c|", buff[i]);
        }

        (void) fp;

        printf("Hello this is in restoration!\n");

        int i = readaline(NULL, NULL);

        (void) i;
        return;
}