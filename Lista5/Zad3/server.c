#include <stdio.h>
#include <string.h>  
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
#include <unistd.h>   
#include <arpa/inet.h>    
#include <sys/socket.h>
#define PORT 8888

struct client{
	int socket;
	char login[10];
};

int main(int argc , char *argv[]) {
	int opt = 1;
	int master_socket , addrlen , new_socket, max_clients = 30 , activity, i , valread , sd;
	struct client clients[30];
	int max_sd;
	struct sockaddr_in address;

	char buffer[1025];
	fd_set readfds;
	char *message = "You connect, please give a login (without space)\n";
	for (i = 0; i < max_clients; i++) {
		clients[i].socket = 0;
	}
	if( (master_socket = socket(AF_INET,SOCK_STREAM,0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);

	if (listen(master_socket, 3) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	addrlen = sizeof(address);
	puts("Waiting for connections ...");

	while(1) {
		FD_ZERO(&readfds);
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
		for ( i = 0 ; i < max_clients ; i++) {
			if(clients[i].socket > 0)
				FD_SET( clients[i].socket , &readfds);
			if(clients[i].socket > max_sd)
				max_sd = clients[i].socket;
		}
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0) && (errno!=EINTR)) 		{
			printf("select error");
		}
		if (FD_ISSET(master_socket, &readfds)) 	{
			if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)	{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
			if( send(new_socket, message, strlen(message), 0) != strlen(message) ) {
				perror("send");
			}
			for (i = 0; i < max_clients; i++) {
				if( clients[i].socket == 0 ){
					strcpy(clients[i].login," ");
					clients[i].socket = new_socket;
					printf("Adding to list of sockets as %d\n" , i);
					break;
				}
			}
		}
		for (i = 0; i < max_clients; i++) {
			if (FD_ISSET( clients[i].socket , &readfds)) {
				if ((valread = read( clients[i].socket , buffer, 1024)) == 0){
					getpeername(clients[i].socket , (struct sockaddr*)&address , (socklen_t*)&addrlen);
					printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
					close( clients[i].socket );
					clients[i].socket = 0;
				}
				else{
					buffer[valread]='\0';
					printf("%s",buffer);
					if(strcmp(clients[i].login," ")==0){
						int j;
						for ( j = 0 ; j < max_clients ; j++) {
							if(clients[j].socket&&strlen(buffer)-1==strlen(clients[j].login) &&strncmp(buffer,clients[j].login,(strlen(buffer)-1))==0)
								break;	
						}
						if(j==max_clients){
							int k=0;
							strncpy(clients[i].login,buffer,(strlen(buffer)-1)>9?9:(strlen(buffer)-1));
							clients[i].login[strlen(buffer)-1]='\0';
							char temp[20];
							strcpy(temp,"Your login ");
							strcat(temp,clients[i].login);
							strcat(temp,". Users in server:\n");
							if(send(clients[i].socket , temp , strlen(temp) , 0 )<0){
								printf("blad\n");
							}
							int l;
							for(l=0;l<max_clients;++l){
								if(clients[l].socket&&strcmp(clients[l].login," ")!=0){
									send(clients[i].socket , clients[l].login , strlen(clients[l].login) , 0 );
									send(clients[i].socket, "\n",strlen("\n"),0);
								}
							}
							send(clients[i].socket, "\n",strlen("\n"),0);
							
						}else{
							send(clients[i].socket , "Please again\n" , strlen("Please again\n") , 0 );
						}
						
					}else{
						int jj;
						char temp[1035];
						for(jj=0;jj<10;jj++){
							if(buffer[jj]!=' ')
								temp[jj]=buffer[jj];
							else{
								int j;
								temp[jj]='\0';
								for ( j = 0 ; j < max_clients ; j++) {
									if(clients[j].socket&&strlen(temp)==strlen(clients[j].login) &&strncmp(temp,clients[j].login,(strlen(temp)))==0)
									{
										strcpy(temp,clients[i].login);
										strcat(temp,(buffer+strlen(clients[j].login)));
										temp[1034]='\0';
										send(clients[j].socket , temp ,strlen(temp) , 0 );
									}
								}
							}
						
						}
					}
				}
			}
		}
	}
	return 0;
} 