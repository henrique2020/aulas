package visualizacao;

import java.util.Scanner;

import entidades.Cliente;
import entidades.Diretor;
import entidades.Funcionario;
import entidades.Gerente;
import entidades.Pessoa;

public class InterfaceDeUsuario {

	private Pessoa[] pessoas = new Pessoa[100];
	private int proximoLivre = 0;
	
	Scanner entrada = new Scanner(System.in);
	
	public void menuPrincipal()
	{
		System.out.println("0.Sair");
		System.out.println("1.Cadastrar Diretor");
		System.out.println("2.Cadastrar Gerente");
		System.out.println("3.Cadastrar Cliente");
		System.out.println("4.Mostrar todos");
		int opcao = entrada.nextInt();
		while(opcao != 0)
		{		
			switch(opcao)
			{
			case 1:
				System.out.print("Nome :");
				entrada.nextLine();
				String nome = entrada.nextLine();
				System.out.print("CPF :");
				String cpf = entrada.nextLine();
				System.out.print("Salario :");
				double sal = entrada.nextDouble();
				Diretor tempDir = new Diretor(nome,cpf);
				tempDir.setSalario(sal);
				pessoas[proximoLivre] = tempDir;
				proximoLivre++;
				break;
			case 2:
				System.out.println("Nome :");
				entrada.nextLine();
				nome = entrada.nextLine();
				System.out.println("CPF :");
				cpf = entrada.nextLine();
				System.out.print("Salario :");
				sal = entrada.nextDouble();
				Gerente tempG = new Gerente(nome,cpf);
				tempG.setSalario(sal);
				pessoas[proximoLivre] = tempG;
				proximoLivre++;
				break;
			case 3:
				System.out.println("Nome :");
				entrada.nextLine();
				nome = entrada.nextLine();
				System.out.println("CPF :");
				cpf = entrada.nextLine();
				System.out.println("Cr�dito :");
				String situacao = entrada.nextLine();
				Cliente tempC = new Cliente(nome,cpf);
				tempC.setSituacaoDeCredito(situacao);
				pessoas[proximoLivre] = tempC;
				proximoLivre++;
				break;
			case 4:
				for(int i=0; i<proximoLivre; i++)
				{
					System.out.println(pessoas[i].getNome());
					//System.out.println(pessoas[i].getSalario());
				}
				for(int i=0; i<proximoLivre; i++)
				{
//					System.out.println(pessoas[i].getNome());
					System.out.println(pessoas[i].getCpf());
				}
				break;
			
			}
			System.out.println("0.Sair");
			System.out.println("1.Cadastrar Diretor");
			System.out.println("2.Cadastrar Gerente");
			System.out.println("3.Cadastrar Cliente");
			System.out.println("4.Mostrar todos");
			opcao = entrada.nextInt();
		}
	}
}
