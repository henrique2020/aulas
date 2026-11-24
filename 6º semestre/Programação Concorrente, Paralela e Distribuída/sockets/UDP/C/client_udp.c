#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MSG 100

/*---------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	struct sockaddr_in endereco_msg;
	int soquete, tamanho;
	char msg[MSG]="";

	if ( argc != 4 ){
		printf("%s <ip> <porta> \"<mensagem>\"\n", argv[0]);
		exit(0);
	}

	soquete = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = inet_addr(argv[1]);
	endereco_servidor.sin_port = htons(atoi(argv[2]));

	//Envia a mensagem
	strcpy(msg, argv[3]);
	sendto(soquete, msg, strlen(msg)+1, 0, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor));
	// Recebe um retorno
	recvfrom(soquete, msg, 100, 0, NULL, NULL);
	printf("%s\n", msg);
}
/*---------------------------------------------------------------------------------------------------*/



