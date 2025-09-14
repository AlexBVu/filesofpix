#ifndef RESTORATION_H_
#define RESTORATION_H_

#include <stdlib.h>
#include <stdbool.h>

#include "readaline.h"
#include "table.h"
#include "seq.h"
#include "atom.h"
#include "assert.h"


void restoration(FILE *fp);
void check(char **datapp, size_t length, 
           Seq_T *originalWords, Table_T *injectedTable, bool *seqFound);

const char *lineCleaning(char **datapp, size_t length, char *cleanLine);
void printState(Seq_T *originalWords);
size_t countWidth(Seq_T *originalWords);

#endif