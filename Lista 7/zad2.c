#include "parser.h"

#define MAX_MEM 4096
#define MAX_LINES 1024
#define ERROR -1

#define ushort unsigned short

static const char* instructions[15] = {
	"JnS",
	"Load",
	"Store",
	"Add",
	"Subt",
	"Input",
	"Output",
	"Halt",
	"Skipcond",
	"Jump",
	"Clear",
	"AddI",
	"JumpI",
	"LoadI",
	"StoreI"
};

int parse(FILE* input_file, ushort* output)
{
  if(input_file == NULL || output == NULL) return ERROR;

  struct line_struct lines[MAX_LINES];
  memset(lines, 0, sizeof(struct line_struct) * MAX_LINES);

  char* line = NULL;
  size_t len;
  int line_counter = 0;

  while(getline(&line, &len, input_file) != -1 && line_counter < MAX_LINES)
  {
		lines[line_counter] = construct_line(line);
    ++line_counter;
	}
  free(line);

  handle_labels(lines, line_counter);

  memset(output, 0, sizeof(ushort) * MAX_MEM);

  for(int i = 0; i < line_counter; ++i)
  {
    printf("line: %d,	label:%s,	opcode: %d,		data: %d,	datalabel: %s\n", lines[i].addr, lines[i].label, lines[i].operation, lines[i].data, lines[i].data_label);
    output[i] = (lines[i].operation << 12) + lines[i].data;
  }

  clear_labels(lines, line_counter);
  return line_counter;
}

struct line_struct construct_line(char* line)
{
  static const char delimiters[] = " \t\n";
  struct line_struct constructed_line;

  char* token = strtok(line, delimiters);
  ushort addr = get_address(token);

  char* label = NULL;
	token = strtok(NULL, delimiters);
	if(strchr(token, ',') != NULL)
  {
		label = get_label(token);
		token = strtok(NULL, delimiters);
	}

  int decimal = 0;
  if(strcmp(token, "Dec") == 0) decimal = 1;
  ushort operation = get_opcode(token);

  ushort data = get_data(token = strtok(NULL, delimiters), decimal);
  char* data_label = NULL;
  if(data == (ushort)ERROR && token != NULL)
  {
    data_label = (char*) malloc(sizeof(char) * strlen(token) + 1);
    strcpy(data_label, token);
  }

  constructed_line.addr = addr;
  constructed_line.label = label;
  constructed_line.operation = operation;
  constructed_line.data = data;
  constructed_line.data_label = data_label;
  return constructed_line;
}

void handle_labels(struct line_struct* lines, int len)
{
  for(int i = 0; i < len; ++i)
  {
		if(lines[i].data == (ushort)ERROR && lines[i].data_label != NULL)
    {
			for(int j = 0; j < len; ++j)
      {
				if(lines[j].label != NULL && strcmp(lines[j].label, lines[i].data_label) == 0)
        {
					lines[i].data = lines[j].addr;
					break;
				}
			}
		}
	}
}

ushort get_address(char* token)
{
  ushort ret = hex_to_dec(token);
  return ret;
}

ushort get_opcode(char* token)
{
  for(ushort i = 0; i < 15; ++i)
  {
    if(strcmp(token, instructions[i]) == 0) return i;
  }
  return 0;
}

ushort get_data(char* token, int isDec)
{
	if(token == NULL) return 0;
	if(isDec == 1) return atoi(token);

	ushort data = hex_to_dec(token);
	if(data != ERROR) return data;
	return ERROR;
}

char* get_label(char* token)
{
  size_t token_len = strlen(token);
	char* newlabel = (char*) malloc(sizeof(char) * token_len);
	strncpy(newlabel, token, token_len - 1);
  newlabel[token_len - 1] = 0;

	return newlabel;
}

ushort hex_to_dec(char* hex)
{
	ushort ret = 0;
	int i = 0;
	while(hex[i] != 0)
  {
		if((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'A' && hex[i] <= 'F')) ++i;
		else return ERROR;
	}

	int base = 1;

	for(int j = i - 1; j >= 0; --j)
  {
		int digit = (hex[j] <= '9') ? hex[j] - '0' : hex[j] - 'A' + 10;
		ret += base * digit;
		base *= 16;
	}
	return ret;
}

void clear_labels(struct line_struct* lines, int len)
{
  for(int i  = 0; i < len; ++i)
  {
    if(lines[i].label != NULL) free(lines[i].label);
    if(lines[i].data_label != NULL) free(lines[i].data_label);
  }
}
