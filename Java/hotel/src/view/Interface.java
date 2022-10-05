package view;

import java.text.SimpleDateFormat;
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
	private Scanner scan = new Scanner(System.in);
	
	private ArrayList <Cliente> cliente = new ArrayList <Cliente>() ;
	private ArrayList <Funcionario> funcionario = new ArrayList <Funcionario> ();
	private ArrayList <Quarto> quarto = new ArrayList <Quarto> ();
	private ArrayList <Reserva> reserva = new ArrayList <Reserva> ();
	
	private int menu_options(){
		System.out.println("1. Cadastrar cliente");
		System.out.println("2. Cadastrar funcionario");
		System.out.println("3. Cadastrar quarto");
		System.out.println("4. Exibir clientes cadastrados");
		System.out.println("5. Exibir quartos disponiveis");
		System.out.println("6. Exibir reservas efetuadas");
		System.out.println("7. Exibir receita prevista por quarto");
		System.out.println("8. Realizar reserva");
		System.out.println("0. Realizar Logoff");
		
		int op = scan.nextInt();
		scan.nextLine();
		
		return op;
	}

	
	private Endereco pega_endereco(){
		Endereco endereco = new Endereco();
		
		System.out.println("Informe os dados de endereco do cliente");
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
		int[] dt = Arrays.stream(scan.nextLine().split("/")).mapToInt(Integer::parseInt).toArray();
		Data data = new Data(dt[0], dt[1]-1, dt[2]);
		
		return data;
	}
	
	
	
	private boolean verifica_quartos_disponiveis(Data data_inicial, Data data_final) {
		ArrayList <Quarto> quartos_disponiveis = new ArrayList <Quarto>();
		boolean disponibilidade;
		for(Quarto auxQuarto : quarto) {
			disponibilidade = true;
			for(Reserva auxReseva : reserva){
				if(auxQuarto.getNumero() == auxReseva.getQuarto().getNumero()) {
					disponibilidade = auxReseva.verificaDisponibilidade(data_inicial, data_final);
					if(!disponibilidade) {
						break;
					}
				}
			}
			if(disponibilidade) {
				quartos_disponiveis.add(auxQuarto);
			}
		}
		
		if(quartos_disponiveis.size() > 0) {
			System.out.println("Quartos disponiveis: ");
			for(Quarto auxQuarto : quartos_disponiveis) {
				System.out.println("+------------------------------");
				System.out.printf("| %d - %s\n", auxQuarto.getNumero(), auxQuarto.getNome());
				System.out.printf("| Diaria R$ %.2f\n", auxQuarto.getDiaria());
			}
			return true;
		}
		else {
			System.out.println("Nenhum quarto disponivel para o periodo selecionado");
			return false;
		}
	}
	
	
	
    public void menu(Funcionario funcionario_logado) {
    	SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");    	
		Cliente temp_cliente;
		Funcionario temp_funcionario;
		Quarto temp_quarto;
		Reserva temp_reserva;
		Data data_inicial, data_final;
		Endereco temp_endereco;
		
		String nome, cpf, metodo_pagamento, telefone, senha;
    	int op, id_cliente, id_funcionario, numero_quarto;
    	boolean disponibilidade;
    	while (true) {
    		op = this.menu_options();
    		switch(op) {
    			
	    		//Sair
				case 0:
					return;
				
				//Cadastrar cliente
				case 1:
					id_cliente = cliente.size() + 1001;
					
					System.out.print("Informe o nome do cliente: ");
					nome = scan.nextLine();
	
					System.out.print("Informe o CPF do cliente: ");
					cpf = scan.nextLine();
	
					System.out.print("Informe um telefone de contato do cliente: ");
					telefone = scan.nextLine();
	
					temp_cliente = new Cliente(id_cliente, nome, cpf, telefone);
	
					//DATA DE NASCIMENTO
					System.out.print("Informe a data de nascimento do cliente (dd/mm/aaaa): ");
					temp_cliente.setData_nascimento(pega_data());
	
					//ENDEREÇO
					temp_cliente.setEndereco(pega_endereco());
	
					//cliente[qtde_cliente++] = temp_cliente;
					cliente.add(temp_cliente);
					temp_cliente = null;
	
					break;
				
				//Cadastrar funcionario
				case 2:
					id_funcionario = funcionario.size() + 1001;
						
					System.out.print("Informe o nome do funcionario: ");
					nome = scan.nextLine();
	
					System.out.print("Defina a senha de acesso do funcionario: ");
					senha = scan.nextLine();
	
					temp_funcionario = new Funcionario(id_funcionario, nome, senha);
	
					funcionario.add(temp_funcionario);
					temp_funcionario = null;
					
					break;
				
				//Cadastrar quarto
		    	case 3:
					temp_quarto = new Quarto();
					
					System.out.print("Informe o numero do quarto: ");
					temp_quarto.setNumero(scan.nextInt());
	
					System.out.print("Informe o andar do quarto: ");
					temp_quarto.setAndar(scan.nextInt());
	
					System.out.print("Informe o valor da diaria: ");
					temp_quarto.setDiaria(scan.nextFloat());
					scan.nextLine();
	
					System.out.print("Informe o nome de quarto: ");
					temp_quarto.setNome(scan.nextLine());
					
					quarto.add(temp_quarto);
					break;
				
				//Exibir clientes cadastrados
			    case 4:
			    	for(Cliente auxCliente : cliente) {
						System.out.println("+------------------------------");
						System.out.printf("| %d - %s\n", auxCliente.getId(), auxCliente.getnome());
						System.out.printf("| CPF: %s\n", auxCliente.getCpf());
						System.out.printf("| Data de nascimento: %s\n", sdf.format(auxCliente.getData_nascimento().getData().getTime()));
						System.out.printf("| Telefone: %s\n", auxCliente.getTelefone());
						temp_endereco = auxCliente.getEndereco();
						System.out.println("| Endereco:");
						System.out.printf("|  -> %s %s, %s, %s - %s\n", temp_endereco.getRua(), temp_endereco.getNumero(), temp_endereco.getBairro(), temp_endereco.getCidade(), temp_endereco.getEstado());
						System.out.printf("|  -> CEP: %s\n", temp_endereco.getCep());
			    	}
					break;
				
				//Exibir quartos disponiveis
				case 5:
					System.out.print("Informe a data inicial (dd/mm/aaaa): ");
					data_inicial = pega_data();
					System.out.print("Informe a data final (dd/mm/aaaa): ");
					data_final = pega_data();
					verifica_quartos_disponiveis(data_inicial, data_final);
					break;
					
				//Exibir reservas efetuadas
				case 6:
					for(Reserva auxReseva : reserva){
						System.out.println("+------------------------------");
						System.out.printf("| Quarto %d (%s)\n", auxReseva.getQuarto().getNumero(), auxReseva.getQuarto().getNome());
						System.out.printf("| Reservado em nome de %s (id: %d)\n", auxReseva.getCliente().getnome(), auxReseva.getCliente().getId());
						System.out.printf("| Check-in: %s\n", sdf.format(auxReseva.getData_de_entrada().getData().getTime()));
						System.out.printf("| Checkout: %s\n", sdf.format(auxReseva.getData_de_saida().getData().getTime()));
						System.out.printf("| Tempo reservado: %d dia(s)\n", auxReseva.getTempo());
						System.out.printf("| Valor da diaria: %.2f\n", auxReseva.getQuarto().getDiaria());
						System.out.printf("| Funcionario(a) responsavel pela reserva: %s (id: %d)\n", auxReseva.getFuncionario().getnome(), auxReseva.getFuncionario().getId());
					}
					break;
				
				//Exibir receita prevista por quarto
				case 7:
					for(Quarto auxQuarto : quarto) {
						float receita = 0;
						int reservas = 0;
						
						for(Reserva auxReseva : reserva){
							if(auxQuarto.getNumero() == auxReseva.getQuarto().getNumero()) {
								reservas++;
								receita += auxReseva.getQuarto().getDiaria()*auxReseva.getTempo();
								
							}
							//System.out.printf("| Quarto %d (%s)\n", auxReseva.getQuarto().getNumero(), auxReseva.getQuarto().getNome());
							//System.out.printf("| Receita prevista: ", auxReseva.getQuarto().getDiaria()*auxReseva.getTempo());
							
						}
						if(reservas > 0) {
							System.out.println("+------------------------------");
							System.out.printf("| Quarto %d (%s)\n", auxQuarto.getNumero(), auxQuarto.getNome());
							System.out.printf("| %d reservas efetuadas\n", reservas);
							System.out.printf("| Receita prevista: %.2f\n", receita);
						}
					}
					break;
				
				//Realizar reserva
				case 8:					
					System.out.print("Informe a data de check-in (dd/mm/aaaa): ");
					data_inicial = pega_data();
					System.out.print("Informe a data de checkout (dd/mm/aaaa): ");
					data_final = pega_data();
					
					disponibilidade = verifica_quartos_disponiveis(data_inicial, data_final);
					if(disponibilidade) {
						temp_quarto = null;
						temp_cliente = null;
						System.out.print("Informe o numero do quarto: ");
						numero_quarto = scan.nextInt();
						
						for(Quarto auxQuarto : quarto) {
							if((auxQuarto.getNumero() == numero_quarto)) {
								temp_quarto = auxQuarto;
								break;
							}
						}
						
						System.out.print("Informe o ID do cliente: ");
						id_cliente = scan.nextInt();
						for(Cliente auxCliente : cliente) {
							if(auxCliente.getId() == id_cliente) {
								temp_cliente = auxCliente;
								break;
							}
						}
						scan.nextLine();	//Limpar buffer
						
						if(temp_quarto != null && temp_cliente != null) {
							System.out.print("Informe o metodo de pagamento: ");
							metodo_pagamento = scan.nextLine();
							
							temp_reserva = new Reserva(funcionario_logado, temp_cliente, temp_quarto, data_inicial, data_final, metodo_pagamento);
							reserva.add(temp_reserva);
							System.out.println("Reserva efetuada!");
						} else {
							System.out.println("Nao foi possivel concluir a reserva, tente novamente!");
						}
					}
					break;
				
				
			}
    		System.out.println();
    	}
    }
    

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		Interface i = new Interface();
		i.cadastra();
		
		Funcionario funcionario_logado;
		int id, op;
		String senha;
		boolean rep = true;
		
		while(rep) {
			System.out.println("1. Realizar login");
			System.out.println("2. Sair");
			op = scan.nextInt();
			scan.nextLine();	//Limpa buffer
			
			switch(op) {
				case 1:
					funcionario_logado = null;
					System.out.print("Informe o ID de acesso: ");
					id = scan.nextInt();
					scan.nextLine();	//Limpa buffer
					System.out.print("Informe a senha de acesso: ");
					senha = scan.nextLine();
					
					for(Funcionario auxFuncionario : i.funcionario) {
						if(auxFuncionario.getId() == id && auxFuncionario.getSenha().equals(senha)) {
							funcionario_logado = auxFuncionario;
							break;
						}
					}
					if(funcionario_logado != null) { i.menu(funcionario_logado); }
					else { System.out.println("ID e/ou senha nao conferem"); }
					break;	
				
				case 2:
					rep = false;
					break;
			}
		}
		scan.close();
	}
	
	
	private void cadastra() {
		Data temp_dt;
		Endereco temp_endereco;

		Cliente temp_cliente;
		//Cliente(int id, String nome, String cpf, String telefone)
		temp_cliente = new Cliente((cliente.size()+1001), "Luana Heloisa Sophie Freitas", "35409355920", "84997416002");
		temp_dt = new Data(4, 8, 1976);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("876", "Rua das Algas", "Ponta Negra", "Natal", "RN", "59090410");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);
		
		temp_cliente = new Cliente((cliente.size()+1001), "Henrique Samuel Silveira", "18143537129", "67995686434");
		temp_dt = new Data(7, 5, 1959);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("403", "Rua Avelina Costa de Andrade", "Jardim Itatiaia", "Campo Grande", "MS", "79042380");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);
		
		temp_cliente = new Cliente((cliente.size()+1001), "Gabrielly Silvana Cecilia de Paula", "30990978702", "84988741984");
		temp_dt = new Data(19, 7, 1979);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("394", "Rua Irenilson Ferreira Júnior", "Aboliçao", "Mossoro", "RN", "59617220");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);

		temp_cliente = new Cliente((cliente.size()+1001), "Vera Analu Aparecida Ribeiro", "74345646790", "21989754902");
		temp_dt = new Data(24, 7, 2002);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("815", "Rua Vicente de Araújo", "Campo Grande", "Rio de Janeiro", "RJ", "23067440");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);

		temp_cliente = new Cliente((cliente.size()+1001), "Barbara Juliana da Rosa", "49517130040", "51995046455");
		temp_dt = new Data(19, 6, 2004);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("359", "Rua Cinco", "Restinga", "Porto Alegre", "RS", "91790033");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);

		temp_cliente = new Cliente((cliente.size()+1001), "Guilherme Renan Raul Brito", "59961026845", "11998270692");
		temp_dt = new Data(17, 11, 1993);
		temp_cliente.setData_nascimento(temp_dt);
		temp_endereco = new Endereco("S/N", "Rua Fabio Leoni Werneck", "Vila Isabel (Parelheiros)", "Sao Paulo", "SP", "04895044");
		temp_cliente.setEndereco(temp_endereco);
		cliente.add(temp_cliente);

		Funcionario temp_funcionario;
		//Funcionario(int id, String nome, String cpf, String telefone)
		temp_funcionario = new Funcionario((funcionario.size()+1001), "Henrique", "");
		funcionario.add(temp_funcionario);
		
		temp_funcionario = new Funcionario((funcionario.size()+1001), "Josefa Marcela Sales", "62358168475");
		funcionario.add(temp_funcionario);

		temp_funcionario = new Funcionario((funcionario.size()+1001), "Emanuel Pedro Henrique Carvalho", "67946974590");
		funcionario.add(temp_funcionario);
		
		Quarto temp_quarto;
		//Quarto(int numero, int andar, float valor, String nome, String tipo)
		temp_quarto = new Quarto(101, 1, (float) 119.69, "Solteiro Standart", "Solteiro");
		quarto.add(temp_quarto);
		temp_quarto = new Quarto(102, 1, (float) 119.69, "Solteiro Standart", "Solteiro");
		quarto.add(temp_quarto);
		temp_quarto = new Quarto(103, 1, (float) 145.00, "Solteiro Deluxy", "Solteiro");
		quarto.add(temp_quarto);
		temp_quarto = new Quarto(201, 2, (float) 139.99, "Casal Standart", "Casal");
		quarto.add(temp_quarto);
		temp_quarto = new Quarto(202, 2, (float) 139.99, "Casal Standart", "Casal");
		quarto.add(temp_quarto);
		temp_quarto = new Quarto(203, 2, (float) 187.00, "Casal Deluxy", "Casal");
		quarto.add(temp_quarto);

		Reserva temp_reserva;
		Data temp_dt_entrada;
		Data temp_dt_saida;
		//Reserva(Funcionario funcionario, Cliente cliente, Quarto quarto, Data data_de_entrada, Data data_de_saida, String metodo_pagamento)
		temp_dt_entrada = new Data(30, 9-1, 2022);
		temp_dt_saida = new Data(7, 10-1, 2022);
		temp_reserva = new Reserva(funcionario.get(1), cliente.get(1), quarto.get(1), temp_dt_entrada, temp_dt_saida, "Cartao");
		reserva.add(temp_reserva);
		
		temp_dt_entrada = new Data(1, 10-1, 2022);
		temp_dt_saida = new Data(4, 10-1, 2022);
		temp_reserva = new Reserva(funcionario.get(0), cliente.get(2), quarto.get(4), temp_dt_entrada, temp_dt_saida, "Dinheiro");
		reserva.add(temp_reserva);
		
		temp_dt_entrada = new Data(7, 10-1, 2022);
		temp_dt_saida = new Data(9, 10-1, 2022);
		temp_reserva = new Reserva(funcionario.get(1), cliente.get(0), quarto.get(1), temp_dt_entrada, temp_dt_saida, "Boleto");
		reserva.add(temp_reserva);
	}
}