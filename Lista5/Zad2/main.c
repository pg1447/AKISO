#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <malloc.h>


#define MAX 100


bool start=0;

int posilki[MAX];
sem_t widelec[MAX];

bool czyGlodny(int id);
void *filozof(void *args){
	int *id;
	id = (int*) args;
	int prawy,lewy;
	
	prawy=((*id)+1)==MAX?0:((*id)+1);
	lewy=((*id)-1)<0?(MAX-1):((*id)-1);
	
	printf("Filozof %d gotowy\n",(*id));
	
	while(!start){
		sleep(1);
	}
	
	while(1){
		sleep(1);
		if(!czyGlodny)
			continue;
		
		sem_wait(&widelec[prawy]);
		while (sem_trywait(&widelec[lewy]) == -1)
			continue;
		printf("Filozof %d je %d\n", (*id), ++posilki[(*id)]);
		sleep(5);
		sem_post(&widelec[prawy]);
		sem_post(&widelec[lewy]);
		printf("Filozof %d mysli\n", (*id));
	}
	
}


int main(){
	int i;
	
	pthread_t th[MAX];
	int *id=malloc(sizeof(int)*MAX);
	
	for( i=0;i<MAX;++i){
		posilki[i]=0;
		sem_init(&widelec[i],0,1);
		id[i]=i;
		pthread_create(&(th[i]), NULL, filozof, (void*) &id[i]);
	}
	start=1;
	sleep(1000);
	for(i=0;i<MAX;++i){
		printf("%d ",posilki[i]);
		if(i%9==0)
			printf("\n");
	}
}


bool czyGlodny(int id){
	return (posilki[id==0?(MAX-1):(id-1)]+2>posilki[id] || (posilki[id==(MAX-1)?0:(id+1)]+2)>posilki[id]);
}