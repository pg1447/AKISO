#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

char* integerToBinary(char *word, int p);
void doubleToBinary(char *word, int p, int how);
int whereIsPoint(char *word);

int main(int argc, char** argv){
	if (argc != 3){
		printf("Składnia: <liczba> <liczba cyfr po przecinku>\n");
		return 1;
	}	
	int p = whereIsPoint(argv[1]);
	printf("%s.",integerToBinary(argv[1],p));
	int how = atoi(argv[2]);
	doubleToBinary(argv[1],p,how);
	printf("\n");
}


void doubleToBinary(char *word, int p, int how){
	int l=strlen(word)-p-1;
	int* number = malloc(sizeof(int) * (l));
	int i;
	for(i=0;i<l;++i)
		number[i]=word[p+1+i]-'0';
	for(i=0; i<how; ++i){
		int j;
		for(j=0; j<l;++j)
			number[j]*=2;
		printf("%d",number[0]>9?1:0);
		number[0]%=10;
		for(j=1;j<l;++j){
			number[j-1]+=number[j]/10;
			number[j]%=10;
			
		}
	}
	free(number);
}

char* integerToBinary(char *word, int p){
	char* inte = malloc((p)*sizeof(char));
	strncpy(inte,word,p);
	int i=1, number = atoi(inte);
	while(pow(2,i)<=number)
		++i;
	char *binaryWord = malloc(i * sizeof(char));
	while(i>0){
		--i;
		binaryWord[i]=number%2+'0';
		number/=2;
	}
	free(inte);
	return binaryWord;
}

int whereIsPoint(char *word){
	int i=0, l=strlen(word);
	for(i=0; i<l; ++i)
		if(word[i]=='.')
			return i;
	return -1;
}