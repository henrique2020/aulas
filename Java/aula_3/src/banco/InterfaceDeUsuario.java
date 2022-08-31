//Criada a função de saque, verificando se o valor sacado é menor ou igual ao saldo
//Criada a função de mostrar saldo
//Depositar e sacar chamam a função ver_saldo()
//Opções transformadas em uma função que é chamada sempre que necessário

package banco;

import java.util.Scanner;

public class InterfaceDeUsuario {

	private Cliente[] cliente = new Cliente[1000];
	private int qtdeClientes = 0;
	private ContaCorrente[] conta = new ContaCorrente[1000];
	private int qtdeContas = 0;

	public void ops(){
		System.out.println("0. Sair");
		System.out.println("1. Cadastrar Cliente");
		System.out.println("2. Cadastrar ContaCorrente");
		System.out.println("3. Depositar em uma conta");
		System.out.println("4. Fazer uma retirada de uma conta");
		System.out.println("5. Mostrar o saldo de uma conta");
		System.out.println("6. Mostrar os nomes e cpfs de todos os clientes cadastrados");
		System.out.println("7. Mostrar os números e saldos de todas as contas cadastradas");
	}
	
	public void mostrarMenuPrincipal() {
		
		Scanner scan = new Scanner(System.in);
		
		//declaração de variáveis auxiliares
		Cliente tempCliente;
		ContaCorrente tempConta;
		int numero, opcao;
		double valor;
		String nome, endereco, cpf;
		
		ops();
		opcao = scan.nextInt();
		
		while(opcao != 0) {
			scan.nextLine();
			switch(opcao) {
			case 1 :
				System.out.println("Forneça o nome do novo cliente");
				nome = scan.nextLine();
				//tempCliente = new Cliente(nome);
				
				System.out.println("Forneça o CPF do novo cliente");
				cpf = scan.nextLine();
				
				tempCliente = new Cliente(nome, cpf);
				
				System.out.println("Forneça o endereço do novo cliente");
				endereco = scan.nextLine();
				tempCliente.setEndereco(endereco);
				
				cliente[qtdeClientes++] = tempCliente;
				break;
			case 2 :
				System.out.println("Forneça o CPF do titular");
				cpf = scan.nextLine();
				
				System.out.println("Forneça o número da conta");
				numero = scan.nextInt();
				
				tempCliente = null;
				for(int i=0 ; i<qtdeClientes; i++) {
					if(cpf.equals(cliente[i].getCpf())) {
						tempCliente = cliente[i];
						break;
					}
				}
				
				if(tempCliente != null) {
					tempConta = new ContaCorrente(tempCliente);
					tempConta.setNumero(numero);
					conta[qtdeContas++] = tempConta;
				}
				else {
					System.out.println("Cliente não encontrado, impossível cadastrar");
				}
				break;
			case 3 :
				System.out.println("Forneça o número da conta");
				numero = scan.nextInt();
				System.out.println("Forneça o valor a ser depositado");
				valor = scan.nextDouble();
				for(int i=0 ; i<qtdeContas ; i++) {
					if(numero == conta[i].getNumero()) {
						conta[i].depositar(valor);
					}
				}
				break;
			case 4 :
				System.out.println("Forneça o número da conta");
				numero = scan.nextInt();
				System.out.println("Forneça o valor a ser retirado");
				valor = scan.nextDouble();
				for(int i=0 ; i<qtdeContas ; i++) {
					if(numero == conta[i].getNumero()) {
						conta[i].sacar(valor);
					}
				}
				break;
			case 5 :
				System.out.println("Forneça o número da conta");
				numero = scan.nextInt();
				for(int i=0 ; i<qtdeContas ; i++) {
					if(numero == conta[i].getNumero()) {
						conta[i].ver_saldo();
					}
				}
				break;
				
			}
			System.out.println();
			ops();
			opcao = scan.nextInt();
		}
		scan.close();
	}
}