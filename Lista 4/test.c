#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	int pipefd[2];
	char buf[1024];
	int i;
	char * s2;

	pipe(pipefd);
	
	s2 = "test potoku";
	write(pipefd[1], s2, strlen(s2));

	i = read(pipefd[0], buf, 1000);
	buf[i]='\0';

	printf("Odczyt %d bajtow z potoku: %s\n", i, buf);
	//printf("%s", ret);
}
