#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>

const int MAX=50;
int id;

void* pobiernie(){
  char old[MAX];
  char* buf;
  while(1){
    sleep(1);
    buf = (char*)shmat(id, NULL, 0);
    if (buf == NULL){
      printf("ERROR shmat odczyt");
      return NULL;
    }else
      if(strcmp(buf,old)!=0){
	printf("%s",buf);
	strcpy(old,buf);
      }
  }
}

int main(int argc, char** argv){
  if(argc<3||strlen(argv[1])>10){
    printf("prosze podac login, mniejszy od 10 znakow oraz id serwera\n");
    return 1;
  }
  int x = atoi(argv[2]);
  id=shmget(x, MAX*sizeof(char), 0666);
  if(id == -1){
   printf("ERROR shmget\n"); 
   return 1;
  }
  pthread_t th;
  pthread_create(&th, NULL, pobiernie, NULL);
  //pthread_join(th,NULL);
  char* buf;
  buf = (char*)shmat(id, NULL, 0);
  if(buf == NULL){
    printf("ERROR shmat\n");
    return 1;
  }
  char znak[MAX];
  int rlogin=strlen(argv[1]);
  strcpy(znak,argv[1]);
  znak[rlogin]=' ';
  while(1){
    fgets(znak+rlogin+1, MAX-(rlogin+1), stdin);
    strcpy(buf,znak);
  }
}