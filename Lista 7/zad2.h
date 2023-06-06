#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct line_struct
{
	char* label;
	char* data_label;
	unsigned short addr;
	unsigned short operation;
	unsigned short data;
};

int parse(FILE* input_file, unsigned short* output);

char* get_label(char* token);
unsigned short get_address(char* token);
unsigned short get_opcode(char* token);
unsigned short get_data(char* token, int isDec);

struct line_struct construct_line(char* line);

void handle_labels(struct line_struct* lines, int len);
void clear_labels(struct line_struct* lines, int len);

unsigned short hex_to_dec(char* hex);

#endif
