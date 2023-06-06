#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>

#define FREE(T) do{ free(T); T = NULL;}while(0)
#define MAX 1000


int **createMatrix(int size)
{
	int **matrix;
	if( (matrix = (int**)malloc(sizeof(int*) * size)) == NULL )
		return NULL;

	int i;
	for(i = 0; i < size; ++i)
		if( (matrix[i] = (int*)malloc(sizeof(int) * size)) == NULL )
			return NULL;
	return matrix;
}

void deleteMatrix(int **matrix,int size)
{
	int i;
	for(i = 0; i < size; ++i)
		FREE(matrix[i]);
	FREE(matrix);
}

void randomMatrix(int **matrix, int size)
{
	int i,j;

	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			matrix[i][j] = rand() % MAX + 1;
}

void copyMatrix(int **from, int** to,int size)
{
	int i,j;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			to[i][j] = from[i][j];
}

int  **matrixTransposition(int **matrix, int size)
{
	int **temp;
	if( (temp = createMatrix(size)) == NULL )
	{
		perror("Za malo pamieci na macierz tymczasowa\n");
		exit(1);
	}

	int i,j;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			temp[j][i] = matrix[i][j];

	return temp;
}

int **mult1(int **matrix1,int **matrix2,int size)
{
	int **result;
	if( (result = createMatrix(size)) == NULL )
	{
		perror("Nie udalo sie przydzielic pamieci na macierz\n");
		exit(1);
	}

	int i,j,k;

	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			for(k = 0; k < size; ++k)
				result[i][j] += matrix1[i][k] * matrix2[k][j];

	return result;
}

int **mult2(int **matrix1, int**matrix2, int size)
{
	int **temp = matrixTransposition(matrix1,size);

	int **result;

	if( (result = createMatrix(size)) == NULL )
	{
		perror("Nie udalo sie przydzielic pamieci na macierz\n");
		exit(1);
	}

	int i,j,k;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			for(k = 0; k < size; ++k)
				result[i][j] += matrix1[i][k] * temp[j][k];

	deleteMatrix(temp,size);

	return result;

}


int main(int argc, char **argv)
{
	if( argc < 2)
	{
		perror("Nie podales rozmiatu macierzy\n");
		return  0;
	}
	
	srand(time(NULL));
	int n;

	if( (n = atoi(argv[1])) == 0 )
	{
		perror("Nieprawidlowy rozmiar macierzy\n");
		return 0;
	}


	int **matrix1;
	if( (matrix1 = createMatrix(n)) == NULL)
	{
		perror("Nie udalo sie przydzielic pamieci na macierz\n");
		return 0;
	}

	int **matrix2;
	if( (matrix2 = createMatrix(n)) == NULL )
	{
		perror("Nie udalo sie przydzielic pamieci na macierz\n");
		return 0;
	}

	randomMatrix(matrix1,n);
	randomMatrix(matrix2,n);
	
	struct timeval start;

	if( gettimeofday(&start,NULL) == -1)
	{
		perror("Blad getTimeOfDay\n");
		return 0;
	}

	int **matrix3 = mult1(matrix1,matrix2,n);
	
	struct timeval end;

	if( gettimeofday(&end,NULL) == -1)
	{
		perror("Blad getTimeOfDay\n");
		return 0;
	}

	double time1 = (double)((end.tv_sec + end.tv_usec / (double)1000000)
			 - (start.tv_sec + start.tv_usec / (double)1000000));
	
	deleteMatrix(matrix3,n);

	if( gettimeofday(&start,NULL) == -1)
	{
		perror("Blad getTimeOfDay\n");
		return 0;
	}

	matrix3 = mult2(matrix1,matrix2,n);

	if( gettimeofday(&end,NULL) == -1)
	{
		perror("Blad getTimeOfDay\n");
		return 0;
	}


	double time2 = (double)((end.tv_sec + end.tv_usec / (double)1000000)
			 - (start.tv_sec + start.tv_usec / (double)1000000));
	

	printf("Zwykle mnozenie : %lf s\n",time1);
	printf("Z transponowaniem : %lf s\n",time2);
	

	deleteMatrix(matrix1,n);
	deleteMatrix(matrix2,n);



	return 0;
}
