package banco;

import java.util.Scanner;

public class InterfaceDeUsuario {

	ContaCorrente[] contas = new ContaCorrente[100];
	int qtdeContas = 0;
	
	public void mostrarMenuPrincipal() {
		Scanner scan = new Scanner(System.in);
		
		System.out.println("0. Sair");
		System.out.println("1. Cadastrar Cliente");
		System.out.println("2. Cadastrar Conta Corrente");
		System.out.println("3. Depositar em uma conta");
		System.out.println("4. Mostrar o saldo de uma conta");
		
		int op = scan.nextInt();
		
		while(op != 0) {
			
			switch(op){
				case 1:
					break;
				case 2:
					int numeroConta = scan.nextInt();
					ContaCorrente aux = new ContaCorrente();
					aux.numero = numeroConta;
					contas[qtdeContas++] = aux;
					break;
				case 3:
					break;
				case 4:
					break;
			}
			
			op = scan.nextInt();
		}
		
		
		scan.close();
	}
	
}
