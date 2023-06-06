
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

static char* tempNazwaProgramu;
static char** tempTab;
static int ile=1;
int fdin=0;

static char* nazwaProgramu;
static char** tab;

int temppipe = 0;

void wykonaj(int isAmp, int* pipefd, int pip, int t1){
	pipe(pipefd);
	
	if(ile==1 && fork()==0){
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(nazwaProgramu, tab);
		exit(0);
	}
	else if(ile>1){
		if(fork()==0){ 
		
			if(pip==0){ 
				dup2(pipefd[1],1);
				close(pipefd[0]);
				execvp(nazwaProgramu, tab);
			}
			else if(pip==(ile-1)){ 
				dup2(fdin,0);
				close(pipefd[0]);
				execvp(nazwaProgramu, tab);
				
			}
			else{
				dup2(pipefd[1], 1);
				dup2(fdin, 0);
				close(pipefd[0]);
				execvp(nazwaProgramu, tab);
			}
		}
		else{
			close(pipefd[1]);
			if(isAmp)
				wait(&t1);
			fdin=pipefd[0];

		}
	}
	else {
		if(isAmp)
			wait(0);	
	}
}

int ilePipow(char* z){
	char * slowo = strtok(z, " ");
	int ile=1;
	while(slowo){
		if(strcmp(slowo,"|")==0){ ile++; }
		slowo = strtok(NULL, " ");
	}
return ile;
}

void main(int argc, char *argv[]){
	char zdanie[55];
	char cpyzdanie[55];
	int isAmp=1;
	int pip=0;
	int ktory=0;
	
	while(gets(zdanie)){
	fdin =0;
		isAmp=1;
		pip=0;
		ktory=0;
		
		strcpy(cpyzdanie, zdanie);
		ile = ilePipow(cpyzdanie);

		char * slowo = strtok(zdanie, " ");
		int ktoraSpacja;
		int t1;
		int pipefd[2];

		while(ktory<ile){

			tab = NULL;
			nazwaProgramu=NULL;
			if(pip>0) nazwaProgramu = strtok(NULL, " ");
			else nazwaProgramu = slowo;
			if(strcmp(nazwaProgramu, "exit") == 0) exit(0);
			tab = malloc(sizeof(char*)*2);
			tab[0]="a.out";
			ktoraSpacja=2;
			slowo=strtok(NULL, " ");
			
			while(1){
				if(!slowo) break;
	
				tab = realloc (tab, sizeof(char*) * (ktoraSpacja+1));
				if(strcmp(slowo,"|") == 0){ 
					break;
				}

				tab[ktoraSpacja-1]=slowo;

				slowo=strtok(NULL, " ");

				ktoraSpacja++;
			}
			tab[ktoraSpacja-1]=NULL;
	
			if(strcmp(tab[ktoraSpacja-2], "&") == 0){
				isAmp=0;
				tab[ktoraSpacja-2]=NULL;
			}

			wykonaj(isAmp, pipefd, pip, t1);
			pip++;
			ktory++;
		}
	}
	printf("ctrl+d\nKONIEC\n");
	exit(0);
}
