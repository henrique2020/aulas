#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/*---------------------------------------------------------------------------------------------------*/
#define MSG 100

/*---------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	int soquete;
	char msg[MSG];
	
	if ( argc != 3 ){
		printf("%s <ip> <porta>\n", argv[0]);
		exit(0);
	}

	soquete = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = inet_addr(argv[1]);
	endereco_servidor.sin_port = htons(atoi(argv[2]));

	connect(soquete, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));

	recv(soquete, msg, MSG, 0);

	printf("%s\n", msg);
	
}
/*---------------------------------------------------------------------------------------------------*/

