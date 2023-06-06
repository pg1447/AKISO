#include<stdio.h>

int main(int argc, char *argv[])
{
	
	for(int i=0; i<=256; i++){
		printf("\033[38;5;%dmHello World\n\033[0m", i);
	}
	return 0;
}
