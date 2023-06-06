#include <stdio.h>
#include <string.h>  
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
#include <unistd.h>   
#include <arpa/inet.h>    
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#define PORT 8888


int main(int argc, char ** argv){
	struct sockaddr_in sn;
	int s, ok,n;
	struct hostent *he;
	fd_set readfds, writefds;
	int sd,valread;
	char buffer[1025];
	struct timeval tv;
	tv.tv_sec=2;
	tv.tv_usec=0;
	int time;
	if (!(he = gethostbyname(argv[1]))) {
		puts("can't gethostname");
		exit(1);
	}
	ok = 0;
	while (!ok) {
		sn.sin_family = AF_INET;
		sn.sin_port  = htons((short)PORT);
		sn.sin_addr.s_addr = *(u_long*)(he->h_addr_list[0]);
	
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket()");
			exit(1);
		}
		ok = (connect(s, (struct sockaddr*)&sn, sizeof(sn)) != -1);
	}
	while(1){
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(ok, &writefds);	
		FD_SET(s, &writefds);
		FD_SET(ok, &readfds);	
		FD_SET(s, &readfds);
		select( s + 1 , &readfds , NULL , NULL , NULL);
		
		time=select( s + 1 , NULL , &writefds , NULL , &tv);
		if (FD_ISSET( s , &readfds)) {
			if ((valread = read( s , buffer, 1024)) == 0){
				printf("Server disconnect");
				exit(1);
			}
			else{
				buffer[valread]='\0';
				printf("%s",buffer);		
			}
		}
		if (FD_ISSET(s , &writefds)){
			buffer[0]='\0';
			fgets(buffer,1024,stdin);
			buffer[strlen(buffer)]='\0';
			if(buffer[0]!='\0')
			send(s , buffer ,strlen(buffer) , 0 );
		}
		
		
			
			
	}
		
	
	
	
}