#include <stdlib.h>
#include <stdio.h>

#include "atom.h"

int main() {

        char *string = Atom_string("Hello\0");

        printf("%s\n", string);


        return 0;
}