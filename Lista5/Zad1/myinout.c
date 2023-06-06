#include "myinout.h"
#include <malloc.h>
#include <stdarg.h>
#include <math.h>

const int MAX=1024;

int sizeOfArray(char* array);
void decTo(int number, int to);
int charToInt(char* test, int *n, int to);
void myscanf(const char * format, ...);
void myprintf(const char* format,...);


void myscanf(const char * format, ...){
	char test[MAX];
	char *source;
	int *number;
	va_list vl;

	read(0, test, MAX);
	va_start(vl, NULL);
	int i=0;
	int n=0;
	while(format[i]){
		if(format[i++]=='%')
		{
			switch(format[i++]){
			case 's':{
				source = va_arg(vl, char*);
				int m=0;
				while(test[n]!=' '&&test[n]!='\n'&&test[n]!='\t'&&test[n]!='\0')
					source[m++]=test[n++];
				source[m]='\0';
				
				}break;
			case 'd':{
				number = va_arg(vl, int*);
				(*number)=charToInt(test, &n, 10);
				}break;	
			case 'x':{
				number = va_arg(vl, int*);
				(*number)=charToInt(test, &n, 16);
				}break;	
			case 'b':{
				number = va_arg(vl, int*);
				(*number)=charToInt(test, &n, 2);
				}break;	
		
			}
		}
	}
	
	

}

void myprintf (const char * format,...){
	int i = 0;
	va_list vl;
	char *source;
	int number;
	char test[1];
	va_start(vl,NULL);
	while(format[i]){
		test[0]=format[i];
		if(test[0]=='%'){
			test[0]=format[++i];
			switch(test[0]){
				case 's':{
					source = va_arg(vl, char*);
					write(1, source, sizeOfArray(source));
				}break;
				case 'd':{
					number = va_arg(vl,int);
					decTo(number,10);
				}break;
				case 'x':{
					number = va_arg(vl,int);
					decTo(number,16);
				}break;
				case 'b':{
					number = va_arg(vl,int);
					decTo(number,2);
				}break;
			}
		}
		else
			write(1,test,1);
		++i;
	}
	va_end(vl);
}

int charToInt(char* test, int *n, int to){
	int tab[32];
	int i=0;
	int b=-1;
	if(test[*n]=='-'){
		b=1;
		++(*n);
	}
		
	while(test[*n]!=' '&&test[*n]!='\n'&&test[*n]!='\t'&&test[*n]!='\0'){
		
		if(test[*n]>'9')
			tab[i++]=test[(*n)++]-'A'+10;
		else
			tab[i++]=test[(*n)++]-'0';
	}
	(*n)++;
	int temp=0;
	int l,m;
	m=i-1;
	for(l=0;l<i;++l,--m){
		temp+=pow(to,m)*tab[l];
	}
	return temp*(b*-1);
}

void decTo(int number, int to){
	int array[32];
	int i;
	i=0;
	char x[1];
	if(number<0){
		x[0]='-';
		write(1,x,1);
		number*=-1;
	}
	while(number){
		array[i++]=number%to;
		number/=to;
	}	
	while(i){
		if(array[--i]>9)
			x[0]=array[i]-10+'A';
		else
			x[0]=array[i]+'0';
		write(1,x,1);
	}
}
int sizeOfArray(char* array){
	int i=0;
	while(array[i])
		++i;
	return i;
}
