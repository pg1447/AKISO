#include "emulator.h"

#define STARTING_ADDRESS 0x100

#define ushort unsigned short

static ushort memory[4096];
static short ac;
static ushort ir;
static ushort mbr;
static ushort pc;
static ushort mar;
static char inputreg;
static char outputreg;
static char operation;

const static ushort data_mask = 0b0000111111111111;

void initialize(FILE* input)
{
  if(input == NULL) return;

  memset(memory, 0, MAX_MEM * sizeof(ushort));

  char byte;
  int bitshift = 0;
  int i = STARTING_ADDRESS;
  while((byte = fgetc(input)) != EOF)
  {
    memory[i] += byte << bitshift;
    if(bitshift == 8)
    {
      ++i;
      bitshift = 0;
    }
    else bitshift = 8;
  }

  pc = STARTING_ADDRESS;
  ac = ir = mbr = mar = 0;
}

void run()
{
  int halt = 0;
  while(halt == 0 && pc < MAX_MEM){
    fetch();
    decode();
    halt = execute();
  }
//  printf("sum: %d\n", memory[276]);
}

void fetch()
{
  mar = pc;
  ir = memory[mar];
  ++pc;
}

void decode()
{
  mar = ir & data_mask;
  operation = ir >> 12;
}

int execute(){
  switch(operation)
  {
    case 0: //JnS
      mbr = pc;
      memory[mar] = mbr;
      mbr = mar;
      ac = 1 + mbr;
      pc = ac;
      break;
    case 1: //Load
      mbr = memory[mar];
      ac = mbr;
      break;
    case 2: //Store
      mbr = ac;
      memory[mar] = mbr;
      break;
    case 3: //Add
      mbr = memory[mar];
      ac += mbr;
      break;
    case 4: //Subt
      mbr = memory[mar];
      ac -= mbr;
      break;
    case 5: //Input
      scanf("%1c", &inputreg);
      ac = inputreg;
      break;
    case 6: //Output
      outputreg = ac;
      printf("%c", outputreg);
      break;
    case 7: //Halt;
      return 1;
    case 8: //Skipcond
      if(mar >> 10 == 0){ if(ac < 0) ++pc; }
      else if(mar >> 10 == 1){ if(ac == 0) ++pc; }
      else if(mar >> 10 == 2){ if(ac > 0) ++pc; }
      break;
    case 9: //Jump
      pc = ir & data_mask;
      break;
    case 10: //Clear
      ac = 0;
      break;
    case 11: //AddI
      mbr = memory[mar];
      mar = mbr;
      mbr = memory[mar];
      ac += mbr;
      break;
    case 12: //JumpI
      mbr = memory[mar];
      pc = mbr;
      break;
    case 13: //LoadI
      mbr = memory[mar];
      mar = mbr;
      mbr = memory[mar];
      ac = mbr;
      break;
    case 14: //StoreI
      mbr = memory[mar];
      mar = mbr;
      mbr = ac;
      memory[mar] = mbr;
      break;
    default:
      return 1;
  }

  return 0;
}
