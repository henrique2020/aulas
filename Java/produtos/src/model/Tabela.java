package model;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Tabela {
	private ArrayList<Produto> produtos;
	private Arquivo dados;
	private int capacidade; // numero maximo de produtos dentro da tabela

	/**
	 * Construtor -> inicializa uma Tabela
	 *
	 * @param produtos   -> inicializa um Array de Produtos
	 * @param dados      -> inicializa o Construtor Arquivo
	 * @param capacidade -> A capacidade maxima da tabela
	 */
	public Tabela(int tamanho_lista, String caminho) {
		this.produtos = new ArrayList<Produto>();
		this.dados = new Arquivo(caminho);
		this.capacidade = tamanho_lista;
	}

	/**
	 * Metodo que insere um produto na tabela
	 *
	 * @param codigo    -> codigo do produto
	 * @param preco     -> preco do produto
	 * @param descricao -> descricao do produto
	 * 
	 * @return inteiro -> 0 - Inseriu
	 *         -> 1 - Nao inseriu, tabela cheia
	 *         -> 2 - Nao inseriu, ja havia um produto com esse codigo
	 */
	public int inserirProduto(int codigo, double preco, String descricao) {

		if (produtos.size() <= capacidade) {
			for (Produto prod : produtos) {
				if (prod.getCodigo() == codigo) {
					return 2;
				}
			}

			if (descricao.contains("impressora")) {
				Impressora produto = new Impressora(codigo, preco, descricao);
				produto.setPreco(produto.correcaoMonetaria(preco));
				produtos.add(produto);
			} else if (descricao.contains("teclado")) {
				Teclado produto = new Teclado(codigo, preco, descricao);
				produto.setPreco(produto.correcaoMonetaria(preco));
				produtos.add(produto);
			} else if (descricao.contains("mouse")) {
				Mouse produto = new Mouse(codigo, preco, descricao);
				produto.setPreco(produto.correcaoMonetaria(preco));
				produtos.add(produto);
			} else {
				Produto produto = new Produto(codigo, preco, descricao);
				produtos.add(produto);
			}

			Collections.sort(produtos, Comparator.comparingInt(Produto::getCodigo));
			return 0;
		}
		return 1;
	}

	/**
	 * Metodo que retorna as informacoes do produto
	 * 
	 * @return Array de Produtos
	 *         -> Se nao houver produtos retorna um array vazio
	 */
	public ArrayList<Produto> listarProdutos() {
		return produtos;
	}

	/**
	 * Metodo que retorna o preco de um produto dado seu codigo.
	 *
	 * @param codigo -> codigo do produto, do qual se quer o preco
	 * @return preco -> preco do produto do codigo informado.
	 *         -> Se o produto nao for encontrado, retorna -1
	 */
	public double precoProduto(int codigo) {
		for (Produto prod : produtos) {
			if (prod.getCodigo() == codigo) {
				return prod.getPreco();
			}
		}
		return -1;
	}

	/**
	 * Metodo que retorna os produtos dentro da faixa de preco.
	 *
	 * @param min -> valor minimo do preco
	 * @param max -> valor maximo do preco
	 * @return Array de Produtos -> array ordenado por preco
	 *         -> Se nao houver produtos retorna um array vazio
	 */
	public ArrayList<Produto> filtrarPreco(double min, double max) {
		ArrayList<Produto> produtos_faixa = new ArrayList<Produto>();
		for (Produto prod : produtos) {
			if (prod.getPreco() >= min && prod.getPreco() <= max) {
				produtos_faixa.add(prod);
			}
		}

		if (produtos_faixa.size() > 0) {
			Collections.sort(produtos_faixa, Comparator.comparingDouble(Produto::getPreco));
		}
		return produtos_faixa;
	}

	public boolean lerDB() {
		try {
			this.produtos = dados.Load();
			return false;
		} catch (IOException e) {
			return true;
		}
	}

	public boolean escreverDB() {
		try {
			dados.Save(produtos);
			return false;
		} catch (IOException e) {
			return true;
		}
	}
}
