#include <stdio.h>

int main(){
	setuid(0);
	execvp("bash",NULL);
	return 0;
}