package view;

import java.util.ArrayList;
import java.util.Scanner;

import model.Produto;
import model.Tabela;

public class Interface {
	private Scanner scan = new Scanner(System.in);
	private Tabela tabela = new Tabela(10, "src/db/products.txt");

	private int menu_options() {
		try {
			System.out.println("1. Inserir produto");
			System.out.println("2. Exibir produtos");
			System.out.println("3. Consultar preco");
			System.out.println("4. Exibir faixa de preco");
			System.out.println("0. Sair");

			int op = scan.nextInt();
			scan.nextLine(); // Limpa buffer

			return op;
		} catch (Exception e) {
			System.out.println("Valor invalido!");
			scan.nextLine(); // Limpa buffer
			return menu_options();
		}
	}

	private int intValidator() {
		try {
			return scan.nextInt();
		} catch (Exception e) {
			System.out.println("Valor invalido!");
			scan.nextLine(); // Limpa buffer
			return intValidator();
		}
	}

	private double doubleValidator() {
		try {
			return scan.nextDouble();
		} catch (Exception e) {
			System.out.println("Valor invalido!");
			scan.nextLine(); // Limpa buffer
			return doubleValidator();
		}
	}

	private void exibe_dados(int codigo, String descricao, double preco) {
		System.out.println("+-----------------");
		System.out.printf("| Codigo: %d\n", codigo);
		System.out.printf("| Descricao: %s\n", descricao);
		System.out.printf("| Preco final: R$%.2f\n", preco);
		System.out.println("+-----------------");
	}

	public void dados(String option) {
		if (option.equals("Ler")) {
			tabela.lerDB();
		} else if (option.equals("Escrever")) {
			tabela.escreverDB();
		}
	}

	public void menu() {
		int op, codigo, retorno;
		String descricao;
		double preco, preco_min, preco_max;
		ArrayList<Produto> produtos;

		while (true) {
			op = this.menu_options();

			switch (op) {
				case 0: // Sair
					return;
				case 1: // Inserir produto
					System.out.print("Codigo: ");
					codigo = intValidator();
					System.out.print("Preco: ");
					preco = doubleValidator();
					scan.nextLine(); // Limpa buffer
					System.out.print("Descricao: ");

					descricao = scan.nextLine();
					retorno = tabela.inserirProduto(codigo, preco, descricao);

					if (retorno == 0) {
						System.out.println("Produto inserido!");
					} else if (retorno == 1) {
						System.out.println("Tabela cheia. Nao e mais possivel inserir produtso");
					} else {
						System.out.println("Este codigo ja foi cadastrado anteriormente");
					}

					break;
				case 2: // Exibir produtos
					produtos = tabela.listarProdutos();
					if (produtos.size() > 0) {
						for (Produto prod : produtos) {
							exibe_dados(prod.getCodigo(), prod.getDescricao(), prod.getPreco());
						}
					} else {
						System.out.println("Nenhum produto cadastrado!");
					}

					break;
				case 3: // Consultar preco
					System.out.print("Codigo: ");
					codigo = intValidator();

					preco = tabela.precoProduto(codigo);
					if (preco >= 0) {
						System.out.printf("Preco: R$%.2f\n", preco);
					} else {
						System.out.println("Codigo nao encontrado");
					}

					break;
				case 4: // Exibir faixa de preco
					System.out.print("Preco minimo: ");
					preco_min = doubleValidator();
					System.out.print("Preco maximo: ");
					preco_max = doubleValidator();

					produtos = tabela.filtrarPreco(preco_min, preco_max);

					if (produtos.size() > 0) {
						System.out.printf("Os seguintes produtos estao entre R$%.2f - R$%.2f:\n", preco_min, preco_max);
						for (Produto prod : produtos) {
							exibe_dados(prod.getCodigo(), prod.getDescricao(), prod.getPreco());
						}
					} else {
						produtos = tabela.listarProdutos();
						if (produtos.size() > 0) {
							System.out.println("Nenhum produto nessa faixa de preco!");
						} else {
							System.out.println("Nenhum produto cadastrado!");
						}
					}

					break;
				case 5:
					System.out.println("Valor invalido");
			}
			System.out.println();
		}
	}
}
