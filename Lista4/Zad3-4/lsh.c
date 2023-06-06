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
void lap(int n){
	if(n==11)
	  exit(0);
}


int main(){
  int i;
  for(i=1;i<=64;++i)
    signal(i,lap);
  char *line=NULL;
  char** command=NULL;
  free(line);
  while(1){
    printf("[kamaz-shell]: ");
    line=getLine();
    if(strcmp(line,"exit\n")==0)
      break;
    if(strcmp(line,"\n")==0){
      continue;
      free(line);
      line=NULL;
    }
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

  int i=0;
  int pipes=0;
  for(i=0;i<last;++i)
     if(0==strcmp(argv[i],"|"))
       ++pipes;
  int p[2];
  int fd_in = 0;
  int count=0;
  int oldcount=0;
  char* temp=NULL;
  
  while(pipes>=0){
    oldcount=count;
    if(pipes==0){
      if(0==strcmp(argv[last],"&")){
	free(argv[last]);
	argv[last]=NULL;
	ampersand=1;
      }
    }else{
	while(0!=strcmp(argv[count],"|")){
	  ++count;
	}
	
	  temp=argv[count];
	  argv[count]=NULL;
	  count++;
    }
    pipe(p);
    int status;
    if ((pid = fork())<0){
      exit(1);
    }else
    if(pid==0){
      dup2(fd_in, 0);
      if (pipes!=0)
      {
	dup2(p[1], 1);
      }
      close(p[0]);
      execvp(argv[oldcount], argv+oldcount);
      exit(0);
      }
      else{
	if(!ampersand)
	  wait(&status);
	
	--pipes;
	close(p[1]);
	fd_in = p[0];
	if(temp!=NULL){
	  argv[count-1]=temp;
	  temp=NULL;
	}
      }
  }
  i=0;
  while(argv[i]!=NULL){
    free(argv[i]);
    argv[i]=NULL;
    ++i;
    }
  free(argv);
  argv=NULL;
}

