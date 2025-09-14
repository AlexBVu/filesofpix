#include "main.h"

int main(int argc, char *argv[]) 
{

        if (argc == 2) {
                FILE *fp = fopen(argv[1], "r");
                if (fp == NULL) {
                  printf("file won't open. Goodbye!\n");
                  exit(EXIT_SUCCESS);
                } else {
                //     printf("file opened\n");
                    restoration(fp);
                }
                fclose(fp);

        } else if (argc == 1) {
                restoration(stdin);
        } else {
                printf("argc is too many\n");
        }
        
        // printf("Hello this is in main!\n");
        
        
        
        exit(EXIT_SUCCESS);
}