#ifndef EMULATOR_H
#define EMULATOR_H

#define MAX_MEM 4096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initialize(FILE* input);
void run();
void fetch();
void decode();
int execute();

#endif
