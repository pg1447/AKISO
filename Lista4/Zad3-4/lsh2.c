#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
const int MAX=100;

char** toCommand(char* args);
char *getLine();
void execute(char** argv);

int main(){
  char *line=NULL;
  char** command=NULL;
  free(line);
  while(1){
    printf("[kamaz-shell]: ");
    line=getLine();
    if(strcmp(line,"exit\n")==0)
      break;
    command=toCommand(line);
    execute(command);
  }
  return 0;
}

char** toCommand(char* args){
  int i=0;
  int words=1;
  while(args[i]!='\n'){
    if(args[i]==' ')
      ++words;
      ++i;
  }
  char **argv;
  argv=(char**)malloc((words+1)*sizeof(char *));
  int j;
  int m=0;
  for(j=0;j<i;++j){
    int temp=0;
    while(args[j]!=' '&&args[j]!='\n'){
      ++temp;
      ++j;
    }
    argv[m]=(char *)malloc(sizeof(char)*(temp+1));
    int k=j-temp;
    int l;
    for(l=0;l<temp;++l){
	argv[m][l]=args[k];
	++k;
    }
    argv[m][l]='\0';
    ++m;
  }
  argv[words]=NULL;
  free(args);
  args=NULL;
  return argv;
}

char *getLine(){
  char* line=malloc(sizeof *line *(MAX));
  fgets(line, MAX-1, stdin);
  line[MAX-1]='\0';
  return line;
}
void execute(char** argv){
  int pid;
  int last=0;
  int ampersand=0;
  while(argv[last]!=NULL)
    ++last;
    --last;
    if(0==strcmp(argv[last],"&")){
      free(argv[last]);
      argv[last]=NULL;
      ampersand=1;
    }
    int status;
    if(fork()==0){
      if(execvp(argv[0],argv)<0){
	printf("Slabo z execvp\n");
	exit(1);
      }
     }
     else{
      if(!ampersand)
      wait(&status);
     }
     int i=0;
     while(argv[i]!=NULL){
       free(argv[i]);
       argv[i]=NULL;
       ++i;
      }
      free(argv);
      argv=NULL;
}

