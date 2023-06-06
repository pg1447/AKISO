#include <unistd.h>
#include <stdio.h>

void main(int argc, char *argv[])
{
	setuid(0);
	execvp("bash",argv);
}
