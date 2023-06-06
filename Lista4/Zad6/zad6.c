#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
const int MAX_VALUE=100;
int a,b,c,t;
int** m1;
int** m2;
int** mw;
int wiersz;
int start=0;
pthread_mutex_t mut;




void* liczeniemacierzy();

int main(){
  printf("Podaj ilosc wierszy i kolumn pierwszej macierzy i ilosc komlumn drugiej macierzy. Oraz liczbe watków ");
  scanf("%d%d%d%d",&a,&b,&c,&t);
  printf("%d %d %d %d\n",a,b,c,t); // Zeby mozna było pomnozyc ilosc kolumn w 1 musi byc rowna ilosc wierszy w m2
  
  m1=(int**)malloc(sizeof(int*)*a);
  int i;
  for(i=0;i<a;++i)
     m1[i]=(int*)malloc(sizeof(int)*b);
  
  m2=(int**)malloc(sizeof(int*)*b);
  for(i=0;i<b;++i)
    m2[i]=(int*)malloc(sizeof(int)*c);
  
  int j;
  printf("Macierz pierwsza \n");
  for(i=0;i<a;++i){
    for(j=0;j<b;++j){
      m1[i][j] = rand() % MAX_VALUE;
      printf("%6d",m1[i][j]);
    }
    printf("\n");
  }
  printf("\nMacierz druga \n");;
  for(i=0;i<b;++i){
    for(j=0;j<c;++j){
      m2[i][j] = rand() % MAX_VALUE;
      printf("%6d",m2[i][j]);
    }
    printf("\n");
  }
  mw=(int**)malloc(sizeof(int*)*a);
  for(i=0;i<a;++i){
     mw[i]=(int*)malloc(sizeof(int)*c);
  }
  pthread_mutex_init(&mut, NULL);
  pthread_t *th;
  th=malloc(sizeof(pthread_t)*t);
  wiersz=0;
  
  for(i=0;i<t;++i){  
    pthread_create(&th[i], NULL, liczeniemacierzy, NULL);
  }
  start =1;
  
  while(t!=0)
    sleep(1);
  printf("\nMacierz wynikowa \n");
  for(i=0;i<a;++i){
    for(j=0;j<c;++j){
      printf("%6d",mw[i][j]);
    }
    printf("\n");
  }
  return 0;
}
  
void* liczeniemacierzy(){
  while(start==0)
    sleep(1);
  int i=-1;
  while(wiersz<a){
    pthread_mutex_lock(&mut);
      i=wiersz;
      wiersz++;
    pthread_mutex_unlock(&mut);
    int j,k;
    if(i>=0&&i<a){
      for(j=0;j<c;++j){
	mw[i][j] = 0;
	for(k=0;k<b;++k){
	  mw[i][j]+=(m1[i][k]*m2[k][j]);
	}
      }
    }
  }
  t--;
  return NULL;
}

  
  
  
  
  
  
  
  
  
  
  
  
  
