#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){

	struct sockaddr_in endereco_cliente, endereco_servidor;
	int soquete;
	int tamanho;

	if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	soquete = socket(AF_INET, SOCK_DGRAM, 0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;
	endereco_servidor.sin_port = htons(atoi(argv[1]));

	bind(soquete, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor));
	char msg[100];
	int tam;
	while (1){
		tam = sizeof(endereco_cliente);
		recvfrom(soquete, msg, 100, 0, (struct sockaddr*) &endereco_cliente, &tam);
		printf("Recebi: %s\n", msg);

		strcpy(msg, "Recebi confia");
		sendto(soquete, msg, strlen(msg)+1, 0, (struct sockaddr*) &endereco_cliente, sizeof(endereco_cliente));
	}
	
}

/*---------------------------------------------------------------------------------------------------*/
