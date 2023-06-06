#include <stdio.h>
#include "parser.h"

#define MAX_MEM 4096

#define ushort unsigned short

int main(int argc, char** argv)
{
  if(argc < 2)
  {
		printf("error: no input file\n");
		return 0;
	}
  if(argc < 3)
  {
    printf("error: no output file\n");
		return 0;
  }

  FILE* asmfile = fopen(argv[1], "r");
  if(asmfile == NULL)
  {
    printf("error: file not found\n");
    return 0;
  }

  ushort output[MAX_MEM];
  int line_counter;
  if((line_counter = parse(asmfile, output)) < 0)
  {
    printf("error: could not parse file\n");
    return 0;
  }
  fclose(asmfile);

  FILE* outputfile = fopen(argv[2], "w");
  fwrite(output, sizeof(ushort), line_counter, outputfile);
  fclose(outputfile);

  return 0;
}
