#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------------*/
#define CONEXOES 10
/*---------------------------------------------------------------------------------------------------*/

int main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	int soquete_servidor, soquete_cliente;
	int tamanho;

	if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;
	endereco_servidor.sin_port = htons(atoi(argv[1]));

}

/*---------------------------------------------------------------------------------------------------*/
