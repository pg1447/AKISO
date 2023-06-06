#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void wykonaj(char * nazwaProgramu, char ** tab, int isAmp){
	int f = fork();
	if(f==-1){
		exit(0);
	}
	else if(f==0){
		execvp(nazwaProgramu, tab);
		exit(0);
	}
	else{
		if(isAmp)
			wait(0);
	}
}

void main(int argc, char *argv[]){
	char zdanie[55];	

	while(gets(zdanie)){
		int isAmp=1;	

		char * slowo = strtok(zdanie, " ");
		char * nazwaProgramu = slowo;
		if(strcmp(nazwaProgramu, "exit") == 0) exit(0);
		char ** tab = NULL;
		tab = malloc(sizeof(char*)*2);
		tab[0]="a.out";
		int ktoraSpacja=2;
		slowo=strtok(NULL, " ");
		while(1){
			if(!slowo) break;
	
			tab = realloc (tab, sizeof(char*) * (ktoraSpacja+1));
		
			tab[ktoraSpacja-1]=slowo;

			slowo=strtok(NULL, " ");

			ktoraSpacja++;
		}
		tab[ktoraSpacja-1]=NULL;
	
		if(strcmp(tab[ktoraSpacja-2], "&") == 0){
			isAmp=0;
			tab[ktoraSpacja-2]=NULL;
		}

		wykonaj(nazwaProgramu, tab, isAmp);
	}
	printf("ctrl+d\nKONIEC\n");
	exit(0);
}
