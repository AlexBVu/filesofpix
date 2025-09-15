#include "main.h"

Except_T main_except = { NULL };

int main(int argc, char *argv[]) 
{


        if (argc == 2) {
                FILE *fp = fopen(argv[1], "r");
                if (fp == NULL) {
                       RAISE(main_except); 
                } else {
                        restoration(fp);
                }
                fclose(fp);

        } else if (argc == 1) {
                restoration(stdin);
        } else {
                RAISE(main_except);
        }
        exit(EXIT_SUCCESS);
}