#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void lap(int n){
	printf("zlapano %d \n",n);
}

int main(){
	int i;
	for(i=1;i<=64;++i){
		signal(i,lap);
	}
	
	int pid=getpid();
	for(i=1;i<=64;++i){
		printf("Wysylanie sygnalu %d ",i);
		kill(pid,i);
		sleep(1);
	}
}
