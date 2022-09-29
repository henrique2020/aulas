package view;

import java.text.SimpleDateFormat;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import model.Cliente;
import model.Funcionario;
import model.Quarto;
import model.Reserva;
import model.Data;
import model.Endereco;

public class Interface {

	//private Cliente[] cliente = new Cliente[1000];
	private ArrayList <Cliente> cliente = new ArrayList <Cliente>() ;
	private int qtde_cliente = 0;
	
	//private Funcionario[] funcionario = new Funcionario[1000];
	private ArrayList <Funcionario> funcionario = new ArrayList <Funcionario> ();
	private int qtde_funcionario = 0;
	
	//private Quarto[] quarto = new Quarto[20];
	private ArrayList <Quarto> quarto = new ArrayList <Quarto> ();
	private int qtde_quarto = 0;
	
	//private Reserva[] reserva = new Reserva[100];
	private ArrayList <Reserva> reserva = new ArrayList <Reserva> ();
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
		//String[] dt = scan.nextLine().split("/");
		//Data data = new Data(Integer.parseInt(dt[0]), Integer.parseInt(dt[1]), Integer.parseInt(dt[2]));
		
		int[] dt = Arrays.stream(scan.nextLine().split("/")).mapToInt(Integer::parseInt).toArray();
		Data data = new Data(dt[0], dt[1]-1, dt[2]);
		
		return data;
	}
	
    public void menu() {
    	SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
    	
		//Calendar data = Calendar.getInstance();
		Data data, d1, d2; 
		data = pega_data();
		d1 = pega_data();
		d2 = pega_data();
		System.out.println("Periodo: "+sdf.format(d1.getData().getTime())+" | "+sdf.format(d2.getData().getTime()));
		System.out.println("Data: "+sdf.format(data.getData().getTime()));
		
		if(data.getData().compareTo(d1.getData()) < 0 || data.getData().compareTo(d2.getData()) > 0) {
			System.out.println("Fora do intervalo");
		}
		else if (data.getData().compareTo(d1.getData()) >= 0 && data.getData().compareTo(d2.getData()) <= 0) {
			System.out.println("Dentro do intervalo");
		}

		System.out.println(ChronoUnit.DAYS.between(d1.getData().toInstant(), d2.getData().toInstant()));
    	
		Cliente temp_cliente;
		Funcionario temp_funcionario;
		Quarto temp_quarto;
		Reserva temp_reserva;
		Data data_inicio_reserva, data_fim_reserva;
		Endereco temp_endereco;
		String nome, cpf, metodo_pagamento, telefone;
    	int op, id, i;
    	boolean rep = true;
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

				//cliente[qtde_cliente++] = temp_cliente;
				cliente.add(temp_cliente);
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

				//funcionario[qtde_funcionario++] = temp_funcionario;
				funcionario.add(temp_funcionario);
				temp_funcionario = null;
				
				break;
	    	case 3:		//Cadastrar Quarto
				temp_quarto = new Quarto();
				
				System.out.print("Informe o numero do quarto: ");
				temp_quarto.setNumero(scan.nextInt());

				System.out.print("Informe o andar do quarto: ");
				temp_quarto.setAndar(scan.nextInt());

				System.out.print("Informe o valor da diaria: ");
				temp_quarto.setDiaria(scan.nextFloat());
				scan.nextLine();

				System.out.println("------------------");
				System.out.println("Nome do quarto");
				System.out.println("Solteiro Standart");
				System.out.println("Casal Standart");
				System.out.println("Solteiro Deluxy");
				System.out.println("Casal Deluxy");
				System.out.println("------------------");
				System.out.print("Informe o nome de quarto: ");
				temp_quarto.setNome(scan.nextLine());
				
				quarto.add(temp_quarto);
				qtde_quarto++;
				break;
		    case 4:		//Consultar disponibilidade de Quartos
				data_inicio_reserva = pega_data();
				data_fim_reserva = pega_data();
				
				

				


				break;
			case 5:		//Realizar reserva
				break;
			case 6:		//Exibir reservas efetuadas
				break;
			case 7:		//Exibir clientes cadastrados
				break;
			case 8:		//Exibir receita prevista por quarto
				for(i = 0; i < reserva.size(); i++) {
					System.out.println(reserva.get(i).getQuarto().getDiaria()*reserva.get(i).getTempo());
					
				}
				break;
			}
    	}
    }


	public static void main(String[] args) {
		Interface i = new Interface();
		i.cadastra();
		i.menu();
	}
	
	private void cadastra() {
		Data temp_dt;
		Endereco temp_endereco;

		Cliente temp_cliente;
		//Cliente(int id, String nome, String cpf, String telefone)
		temp_cliente = new Cliente((qtde_cliente+1001), "Luana Heloisa Sophie Freitas", "35409355920", "84997416002");
		temp_dt = new Data(4, 8, 1976);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("876", "Rua das Algas", "Ponta Negra", "Natal", "RN", "59090410");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;
		
		temp_cliente = new Cliente((qtde_cliente+1001), "Henrique Samuel Silveira", "18143537129", "67995686434");
		temp_dt = new Data(7, 5, 1959);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("403", "Rua Avelina Costa de Andrade", "Jardim Itatiaia", "Campo Grande", "MS", "79042380");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;
		
		temp_cliente = new Cliente((qtde_cliente+1001), "Gabrielly Silvana Cecília de Paula", "30990978702", "84988741984");
		temp_dt = new Data(19, 7, 1979);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("394", "Rua Irenilson Ferreira Júnior", "Abolição", "Mossoró", "RN", "59617220");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;

		temp_cliente = new Cliente((qtde_funcionario+1001), "Vera Analu Aparecida Ribeiro", "74345646790", "21989754902");
		temp_dt = new Data(24, 7, 2002);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("815", "Rua Vicente de Araújo", "Campo Grande", "Rio de Janeiro", "RJ", "23067440");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;

		temp_cliente = new Cliente((qtde_funcionario+1001), "Bárbara Juliana da Rosa", "49517130040", "51995046455");
		temp_dt = new Data(19, 6, 2004);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("359", "Rua Cinco", "Restinga", "Porto Alegre", "RS", "91790033");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;

		temp_cliente = new Cliente((qtde_funcionario+1001), "Guilherme Renan Raul Brito", "59961026845", "11998270692");
		temp_dt = new Data(17, 11, 1993);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("S/N", "Rua Fábio Leoni Werneck", "Vila Isabel (Parelheiros)", "São Paulo", "SP", "04895044");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente); qtde_cliente++;

		Funcionario temp_funcionario;
		//Funcionario(int id, String nome, String cpf, String telefone)
		temp_funcionario = new Funcionario((qtde_funcionario+1001), "Josefa Marcela Sales", "62358168475");
		temp_funcionario.setTelefone("31982159848");
		temp_dt = new Data(15, 3, 1998);
		temp_funcionario.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("299", "Rua Flor das Pedras", "Brodoski", "Betim", "MG", "32616530");
		temp_funcionario.setEndereco(temp_endereco);
		funcionario.add(temp_funcionario); qtde_funcionario++;

		temp_funcionario = new Funcionario((qtde_funcionario+1001), "Emanuel Pedro Henrique Carvalho", "67946974590");
		temp_funcionario.setTelefone("35986884563");
		temp_dt = new Data(11, 6, 1956);
		temp_funcionario.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("561", "Nossa Senhora Aparecida", "Nossa Senhora Aparecida", "Poços de Caldas", "MG", "37701804");
		temp_funcionario.setEndereco(temp_endereco);
		funcionario.add(temp_funcionario); qtde_funcionario++;
		
		Quarto temp_quarto;
		//Quarto(int numero, int andar, float valor, String nome, String tipo)
		temp_quarto = new Quarto(101, 1, (float) 119.69, "Solteiro Standart", "Solteiro");
		quarto.add(temp_quarto); qtde_quarto++;
		temp_quarto = new Quarto(102, 1, (float) 119.69, "Solteiro Standart", "Solteiro");
		quarto.add(temp_quarto); qtde_quarto++;
		temp_quarto = new Quarto(103, 1, (float) 145.00, "Solteiro Deluxy", "Solteiro");
		quarto.add(temp_quarto); qtde_quarto++;
		temp_quarto = new Quarto(201, 2, (float) 139.99, "Casal Standart", "Casal");
		quarto.add(temp_quarto); qtde_quarto++;
		temp_quarto = new Quarto(202, 2, (float) 139.99, "Casal Standart", "Casal");
		quarto.add(temp_quarto); qtde_quarto++;
		temp_quarto = new Quarto(202, 3, (float) 187.00, "Casal Deluxy", "Casal");
		quarto.add(temp_quarto); qtde_quarto++;

		Reserva temp_reserva;
		//Reserva(Funcionario funcionario, Cliente cliente, Quarto quarto, Data data_de_entrada, Data data_de_saida, String metodo_pagamento)
		//Reserva(int id_funcionario, int id_cliente, Quarto quarto, Data data_de_entrada, Data data_de_saida, String metodo_pagamento)


	}
}