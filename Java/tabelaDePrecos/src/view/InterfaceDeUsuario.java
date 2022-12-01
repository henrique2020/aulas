package view;

import java.util.Scanner;
import model.TabelaDePrecos;

public class InterfaceDeUsuario {

	private TabelaDePrecos tabela = new TabelaDePrecos(100);
	private Scanner entrada = new Scanner(System.in);
	
	public void menu(){
		// variaveis locais
		int codigo, opcao;
		String descricao;
		double preco;
		
		System.out.println("0.Sair");
		System.out.println("1.Inserir produto na tabela");
		System.out.println("2.Consultar preco");
		opcao = entrada.nextInt();
		while(opcao!=0) {
			switch(opcao){
			case 1: //Inserir produto na tabela
				System.out.print("Codigo: ");
				codigo = entrada.nextInt();
				System.out.print("Preco: ");
				preco = entrada.nextDouble();
				System.out.print("Descricao: ");
				descricao = entrada.nextLine();
				tabela.inserirProduto(codigo, preco,descricao);
				
				// completar
				
				break;

			case 2: //Consultar preco
				System.out.print("Codigo: ");
				codigo = entrada.nextInt();

				// completar
				
				break;
			}
			System.out.println("0.Sair");
			System.out.println("1.Inserir produto na tabela");
			System.out.println("2.Consultar pre�o");
			opcao = entrada.nextInt();
		}


	}
	
}
