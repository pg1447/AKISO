#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

struct Stack{
	bool values[4];
	struct Stack* next;
};

struct Stack* putA(struct Stack* now);
struct Stack* putB(struct Stack* now);
struct Stack* and(struct Stack* now);
struct Stack* or(struct Stack* now);
struct Stack* not(struct Stack* now);
void push(struct Stack* now);

int main(int argc, char** argv){
	struct Stack* start=NULL;
	if(argc!=2){
		printf("rownianie\n");
		return 1;
	}
	int i=0,length = strlen(argv[1]);
	
	while(i<length){
		switch(argv[1][i]){
			case 'A':{
				start=putA(start);	
			}break;
			case 'B':{
				start=putB(start);
			}break;
			case '+':{
				start=or(start);
			}break;
			case '*':{
				start=and(start);
			}break;
			case '\'':{
				start=not(start);
			}break;
		}
		++i;
	}
	push(start);
}

struct Stack* putA(struct Stack* now){
	if(now==NULL){
		now = malloc(sizeof(struct Stack));
		now->next=NULL;
		now->values[0]=0;
		now->values[1]=0;
		now->values[2]=1;
		now->values[3]=1;
	}else
		now->next=putA(now->next);
	return now;
	
}
struct Stack* putB(struct Stack* now){
	if(now==NULL){
		now = malloc(sizeof(struct Stack));
		now->next=NULL;
		now->values[0]=0;
		now->values[1]=1;
		now->values[2]=0;
		now->values[3]=1;
	}else
		now->next=putB(now->next);
	return now;
}

struct Stack* and(struct Stack* now){
	if(now->next->next!=NULL)
		now->next=and(now->next);
	else{
		int i=0;
		for(i=0; i<4; ++i)
			now->values[i]*=now->next->values[i];
		free(now->next);
		now->next=NULL;
	}
	return now;
}
struct Stack* or(struct Stack* now){
	if(now->next->next!=NULL)
		now->next=and(now->next);
	else{
		int i=0;
		for(i=0; i<4; ++i)
			now->values[i]+=now->next->values[i];
		free(now->next);
		now->next=NULL;
	}
	return now;
}


struct Stack* not(struct Stack* now){
	if(now->next!=NULL)
		now->next=not(now->next);
	else{
		int i;
		for(i=0;i<4;++i)
			now->values[i]=!now->values[i];
	}
	return now;
}

void push(struct Stack* now){
	int i;
	printf(" A B F\n");
	struct Stack* A = NULL;
	struct Stack* B = NULL;
	A=putA(A);
	B=putB(B);
	for(i=0;i<4;++i)
		printf(" %d %d %d\n", A->values[i],B->values[i],now->values[i]);
}