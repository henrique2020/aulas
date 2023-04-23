#include <stdio.h>

/*-------------------------------------------------*/
#define N 5
/*-------------------------------------------------*/
struct data {
	int dia;
	int mes;
	int ano;
};
typedef struct data DATA;

struct funcionario {
		int codigo;
		char nome[50];
		DATA nascimento;
		float valor_hora;
};
typedef struct funcionario FUNCIONARIO;

/*-------------------------------------------------*/
void le_funcionarios(FUNCIONARIO vetor[N]){
	int i;

	for(i=0; i<N; i++){
		printf("Digite o codigo do funcionario:\n");
		scanf("%d", &vetor[i].codigo);
		fflush(stdin);
		printf("Digite o nome do funcionario:\n");
		gets(vetor[i].nome);
		printf("Digite o dia de nascimento do funcionario:\n");
		scanf("%d", &vetor[i].nascimento.dia);
		printf("Digite o mes de nascimento do funcionario:\n");
		scanf("%d", &vetor[i].nascimento.mes);
		printf("Digite o ano de nascimento do funcionario:\n");
		scanf("%d", &vetor[i].nascimento.ano);
		printf("Digite o valor hora do funcionario:\n");
		scanf("%f", &vetor[i].valor_hora);

	}		
}

/*-------------------------------------------------*/
FUNCIONARIO  mais_velho ( FUNCIONARIO vetor[N]){
	FUNCIONARIO m = vetor[0];
	int i;
	
	for(i=1; i<N; i++){
		if (vetor[i].nascimento.ano * 10000 + vetor[i].nascimento.mes * 100 + vetor[i].nascimento.dia <
		    m.nascimento.ano * 10000 + m.nascimento.mes * 100 + m.nascimento.dia){
		    m = vetor[i];
		}
 	}
	return m;
}

/*-------------------------------------------------*/
int main(){
	FUNCIONARIO vetor[N];
	FUNCIONARIO m;

	le_funcionarios(vetor);
	
	m = mais_velho(vetor);	

	printf("Nome: %s\n", m.nome);
	printf("Dia de nascimento: %d/%d/%d\n", m.nascimento.dia, m.nascimento.mes, m.nascimento.ano);
}
/*-------------------------------------------------*/
