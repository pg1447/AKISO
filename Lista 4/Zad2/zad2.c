#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void wypisz(int sygnal);

void* watek(void* _arg);

void* wypiszWatek(void* _arg);

void main(int argc, char *argv[]){

	if(argc==1){
		printf("Podaj czesc zadania (1/2/3)\n");
		exit(0);
	}
	
	if(strcmp(argv[1], "1") == 0){
		printf("Podpunkt 1\n");

		int id = fork();

		if(id==0){
			for(int i=1 ; i<=64 ; i++){
			signal(i, wypisz);}
			for(;;);
		}
		else
		{	sleep(3);
			for(int i=1 ; i<=64 ; i++){
				sleep(1);
				int k = kill(id, i);
			}
		}
	}


	else if(strcmp(argv[1], "2") ==0){
		printf("Podpunkt 2\n");
		for(int i=1 ; i<=64 ; i++){
			sleep(1);
			kill(1, i); 
		}
	}


	else if(strcmp(argv[1], "3") == 0){
		printf("Podpunkt 3\n");
		pthread_t id1;
		pthread_create(&id1, NULL, watek, NULL);
		pthread_join(id1, NULL);
	}
 
}

void wypisz(int sygnal){
	printf("Odebralem sygnal %d\n", sygnal);
}

void* watek(void* _arg){
	printf("Jestem pierwszym watkiem\n");
	pthread_t id2;
	pthread_create(&id2, NULL, wypiszWatek, NULL);
	pthread_join(id2, NULL);
	return NULL;
}

void* wypiszWatek(void* _arg){
	printf("Jestem watkiem wywolanym przez watek\n");
	return NULL;
}
