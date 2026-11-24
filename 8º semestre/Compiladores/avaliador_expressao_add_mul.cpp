//avaliador de expressoes de soma recursivo a direita

#include <stdio.h>
#include <stdlib.h>

int pos = 0;
char exp[20];

int T(int *Tval);
int E(int *Eval);

int B(int *Bval) {
    int Eval;
    if (exp[pos] == '(') {
		pos++;
		if(E(&Eval)) {
			if(exp[pos] == ')') {
				pos++;
				*Bval = Eval;
				return 1;
			}
			else { return 0; }
		}
		else { return 0; }
	}

	if (exp[pos] < '0' || exp[pos] > '9') { return 0; }
	
	int valor = 0;
	while (exp[pos] >= '0' && exp[pos] <='9' ) {
	   	valor = valor * 10 + exp[pos] - '0';
	   	pos++;
	}
	*Bval=valor;
	return 1;
}

// E ->  T + E1  |  T
int E(int *Eval) {
	int Tval, E1val;
	if (T(&Tval)) {
		if(exp[pos]=='+') {
            pos++;
			if(E(&E1val)) {
				*Eval = E1val + Tval;
				return 1;
			}
            else { return 0; }
		}
		else if(exp[pos]=='-') {
            pos++;
			if(E(&E1val)) {
				*Eval = Tval - E1val;
				return 1;
			}
            else { return 0; }
		}
		else {
			*Eval = Tval;
			return 1;
		}
	} 
	else { return 0; }

}

// T ->  B * T1  |   B / T1  |  B
// B -> digito {B.val=digito}
int T(int *Tval) {
	int Bval, T1val;

	if (B(&Bval)) {
		if(exp[pos]=='*') {
            pos++;
			if(T(&T1val)) {
				*Tval = T1val * Bval;
				return 1;
			}
            else { return 0; }
		}
		else if(exp[pos]=='/') {
            pos++;
			if(T(&T1val)) {
				*Tval = Bval / T1val;
				return 1;
			}
            else { return 0; }
		}
		else {
			*Tval = Bval;
			return 1;
		}
	}
	else { return 0; }
}


/*******************************************************************************************************************/
/*******************************************************************************************************************/
int main()
{
	int Eval;
	printf("Digite a expressao:");
	scanf("%s",exp);
 	if (E(&Eval))  printf("\nExpressao correta vale %d\n",Eval);
	else printf("Erro na posicao %d\n",pos);
	system("pause");
}
/*******************************************************************************************************************/
