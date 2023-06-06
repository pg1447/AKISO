#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>


void first(int **macierz1, int **macierz2, int **macierz3, int n);
void second(int **macierz1, int **macierz2, int **macierz3, int n);

int main( int argc, char** argv){
	if(argc!=2){
		printf("<liczba>\n");
		return 1;
	}
	
	int n=atoi(argv[1]);
	int **macierz1 = malloc(sizeof(int*)*n);
	int **macierz2 = malloc(sizeof(int*)*n);
	int **macierz3 = malloc(sizeof(int*)*n);
	int **macierz4 = malloc(sizeof(int*)*n);
	
	int i,j;
	for(i=0;i<n;++i){
		macierz1[i]=malloc(sizeof(int)*n);
		macierz2[i]=malloc(sizeof(int)*n);
		macierz3[i]=malloc(sizeof(int)*n);
		macierz4[i]=malloc(sizeof(int)*n);
	}
	
	srand(time(NULL));
	for( i=0; i<n; i++)
		for(j=0; j<n;j++){
			macierz1[i][j]=rand()%4;
			macierz2[i][j]=rand()%4;
			macierz3[i][j]=0;
			macierz4[i][j]=0;
		}
	first(macierz1,macierz2,macierz3,n);
	second(macierz1,macierz2,macierz4,n);
}

void first(int **macierz1, int **macierz2, int **macierz3,int n){
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	int i,j,k;
	for (i=0; i<n; ++i)
		for(j=0; j<n; ++j)
			for(k=0; k<n; ++k)
				macierz3[i][j] += macierz1[i][k] * macierz2[k][j];		
	gettimeofday(&t2,NULL);
	double time=t2.tv_sec - t1.tv_sec;
	printf("Bez transpozycji: %f\n", time);
}
void second(int **macierz1, int **macierz2, int **macierz4, int n){
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	int temp[n][n];
	int i,j,k;
	for (i=0; i<n; i++)
		for(j=0; j<n; j++)
			temp[i][j] = macierz2[j][i];
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			for (k=0; k<n; k++)
				macierz4[i][j] += macierz1[i][k] * temp[j][k];

	gettimeofday(&t2, NULL);
	double time = t2.tv_sec - t1.tv_sec;
	printf("Z transpozycja: %f\n",time);
}
