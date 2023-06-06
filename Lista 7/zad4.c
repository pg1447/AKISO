#include <stdio.h>
#include "emulator.h"

int main(int argc, char** argv)
{
  FILE* inputfile = fopen(argv[1], "r");
  initialize(inputfile);
  run();
  fclose(inputfile);
  return 0;
}
