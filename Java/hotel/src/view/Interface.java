package view;

import java.util.Scanner;
import model.Cliente;
import model.Funcionario;
import model.Quarto;
import model.Reserva;
import model.Data;
import model.Endereco;

public class Interface {

	private Cliente[] cliente = new Cliente[1000];
	private int qtde_cliente = 0;
	
	private Funcionario[] funcionario = new Funcionario[1000];
	private int qtde_funcionario = 0;
	
	private Quarto[] quarto = new Quarto[20];
	private int qtde_quarto = 0;
	
	private Reserva[] reserva = new Reserva[100];
	private int qtde_reserva = 0;
	
	private Scanner scan = new Scanner(System.in);
	
	private int menu_options(){
		System.out.println("0. Sair");
		System.out.println("1. Cadastrar Cliente");
		System.out.println("2. Cadastrar Funcionario");
		System.out.println("3. Cadastrar Quarto");
		System.out.println("4. Consultar disponibilidade de Quartos");
		System.out.println("5. Realizar reserva");
		System.out.println("6. Exibir reservas efetuadas");
		System.out.println("7. Exibir clientes cadastrados");
		System.out.println("8. Exibir receita prevista por quarto");
		
		int op = scan.nextInt();
		scan.nextLine();
		
		return op;
	}

	private Endereco pega_endereco(){
		Endereco endereco = new Endereco();
		
		System.out.println("Informe os dados de endereço do cliente");
		System.out.print("Numero: ");
		endereco.setNumero(scan.nextLine());
		System.out.print("Rua: ");
		endereco.setRua(scan.nextLine());
		System.out.print("Bairro: ");
		endereco.setBairro(scan.nextLine());
		System.out.print("Cidade: ");
		endereco.setCidade(scan.nextLine());
		System.out.print("Estado: ");
		endereco.setEstado(scan.nextLine());
		System.out.print("CEP: ");
		endereco.setCep(scan.nextLine());

		return endereco;
	}

	private Data pega_data(){
		String[] dt = scan.nextLine().split("/");
		Data data = new Data(Integer.parseInt(dt[0]), Integer.parseInt(dt[0]), Integer.parseInt(dt[0]));
		
		return data;
	}
	
    public void menu() {
		Cliente temp_cliente;
		Funcionario temp_funcionario;
		Quarto temp_quarto;
		Reserva temp_reserva;
		Data data_nascimento, temp_data;
		Endereco temp_endereco;
		String nome, cpf, metodo_pagamento, telefone;
    	int op, id;
    	boolean rep = true;
		String[] dt;
    	while (rep) {
    		op = this.menu_options();
    		switch(op) {
			case 0:		//Sair
				rep = false;
				break;
			case 1:		//Cadastrar Cliente
				id = qtde_cliente + 1001;
				
				System.out.print("Informe o nome do cliente: ");
				nome = scan.nextLine();

				System.out.print("Informe o CPF do cliente: ");
				cpf = scan.nextLine();

				System.out.print("Informe um telefone de contato do cliente: ");
				telefone = scan.nextLine();

				temp_cliente = new Cliente(id, nome, cpf, telefone);

				//DATA DE NASCIMENTO
				System.out.print("Informe a data de nascimento do cliente (dd/mm/aaaa): ");
				temp_cliente.setData_nascimento(pega_data());

				//ENDEREÇO
				temp_cliente.setEndereco(pega_endereco());

				cliente[qtde_cliente++] = temp_cliente;
				temp_cliente = null;

				break;
			case 2:		//Cadastrar Funcionario
				id = qtde_funcionario + 1001;
					
				System.out.print("Informe o nome do funcionario: ");
				nome = scan.nextLine();

				System.out.print("Informe o CPF do funcionario: ");
				cpf = scan.nextLine();

				temp_funcionario = new Funcionario(id, nome, cpf);

				System.out.print("Informe um telefone de contato do funcionario: ");
				telefone = scan.nextLine();
				temp_funcionario.setTelefone(telefone);

				//DATA DE NASCIMENTO
				System.out.print("Informe a data de nascimento do cliente (dd/mm/aaaa): ");
				temp_funcionario.setData_nascimento(pega_data());

				//ENDEREÇO
				temp_funcionario.setEndereco(pega_endereco());

				funcionario[qtde_funcionario++] = temp_funcionario;
				temp_funcionario = null;
				
				break;
	    	case 3:		//Cadastrar Quarto
				temp_quarto = new Quarto();
				
				System.out.print("Informe o numero do quarto: ");
				temp_quarto.setNumero(scan.nextInt());

				System.out.print("Informe o andar do quarto: ");
				temp_quarto.setAndar(scan.nextInt());

				System.out.print("Informe o valor da diaria: ");
				temp_quarto.setValor(scan.nextFloat());
				scan.nextLine();

				System.out.println("------------------");
				System.out.println("Tipos de quarto");
				System.out.println("Solteiro Standart");
				System.out.println("Casal Standart");
				System.out.println("Solteiro Deluxy");
				System.out.println("Casal Deluxy");
				System.out.println("------------------");
				System.out.print("Informe o tipo de quarto: ");
				temp_quarto.setTipo(scan.nextLine());
				break;
		    case 4:		//Consultar disponibilidade de Quartos
				break;
			case 5:		//Realizar reserva
				break;
			case 6:		//Exibir reservas efetuadas
				break;
			case 7:		//Exibir clientes cadastrados
				break;
			case 8:		//Exibir receita prevista por quarto
				break;
			}
    	}
    }
    
}