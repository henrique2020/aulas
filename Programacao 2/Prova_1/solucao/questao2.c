#include <stdio.h>

//-----------------------------------------------------
#define N 5

//-----------------------------------------------------
void le_matriz(float mat[N][N]){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			printf("Digite o valor:\n");
			scanf("%f", &mat[i][j]);
		}
	}
}
//-----------------------------------------------------
void escreve_matriz(float mat[N][N]){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			printf("% 5.2f", mat[i][j]);
		}
		printf("\n");
	} 
}
//-----------------------------------------------------
void ordena_matriz(float mat[N][N]){
	int cont[N];
	int i, j, k, iaux;
	float faux;
	
	for(i=0; i<N; i++){
		cont[i] = 0;
		for(j=0; j<N; j++){
			if ( mat[i][j] == 0 ){
				cont[i]++;
			}
		}
	}
	
	for(i=0; i<N-1; i++){
		for(j=0; j<N-1; j++){
			if (cont[j] < cont[j+1]){
				iaux = cont[j];
				cont[j] = cont[j+1];
				cont[j+1] = iaux;
				for(k=0; k<N; k++){
					faux = mat[j][k];
					mat[j][k] = mat[j+1][k];
					mat[j+1][k] = faux;
				}	
			}
		}
	}
}

//-----------------------------------------------------
int main(){
	float mat[N][N];
	
	le_matriz(mat);
	printf("------------------------\n");
	escreve_matriz(mat);
	ordena_matriz(mat);
	printf("------------------------\n");
	escreve_matriz(mat);
}
