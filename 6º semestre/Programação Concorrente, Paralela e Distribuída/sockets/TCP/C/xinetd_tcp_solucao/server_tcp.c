#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*---------------------------------------------------------------------------------------------------*/
#define CONEXOES 10
#define MSG 100
/*---------------------------------------------------------------------------------------------------*/

int main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	int soquete_servidor, soquete_cliente;
	int tamanho;
	char msg[MSG];

	if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	soquete_servidor = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;
	endereco_servidor.sin_port = htons(atoi(argv[1]));

	bind(soquete_servidor, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));

	listen(soquete_servidor, CONEXOES);

	while ( 1 ){

		soquete_cliente = accept(soquete_servidor, NULL, NULL);

		strcpy(msg,"Servidor: Ola Mundo");

		send(soquete_cliente, msg, strlen(msg)+1, 0);

		close(soquete_cliente);
	}
	close(soquete_servidor);

}

/*---------------------------------------------------------------------------------------------------*/
