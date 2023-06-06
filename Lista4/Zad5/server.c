#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>
const int MAX = 50;

int main(char argc,char **argv){
  if(argc<2){
    printf("prosze podac numer \n");
    return 0;
  }
  int id;
  int x=atoi(argv[1]);
  id=shmget(x, MAX*sizeof(char),IPC_CREAT|0666);
  if(id == -1){
   printf("ERROR shmget\n"); 
   return 1;
  } 
  char* buf = (char*)shmat(id, NULL, 0);
  if(buf == NULL){
    printf("ERROR shmat\n");
    return 1;
  }
  strcpy(buf,"Witamy na serwerze\n");
  printf("Stworzono punkt komunikacji:%d \n NAcisni znak aby zakonczyc\n",id);
  getchar();
  if (shmctl ( id, IPC_RMID, NULL )==-1)
    printf("nie udalo sie\n");
  return 0;
}