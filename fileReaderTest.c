#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *datapp;
	char line[20];
	int i = 0;

	FILE *fp = fopen(argv[1], "r");

        char curr = fgetc(fp);

	while (curr != '\n') {
                line[i++] = curr;
                curr = fgetc(fp);
	}

        datapp = line;
        for (int j = 0; j < i; j++) {
                printf("datapp is %c\n", datapp[j]);
        }
	fclose(fp);
	return 0;
}
