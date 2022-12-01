package model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Tabela {
	private ArrayList <Produto> produtos;
	private int capacidade ;  // numero maximo de produtos dentro da tabela

	/**
	 * Construtor	-> inicializa uma Tabela
	 * 				-> especifica o tamanho mamixo 
	 *
	 * @param capacidade -> A capacidade maxima da tabela
	 */
	public Tabela(int tamanho_lista){
		this.produtos = new ArrayList <Produto>();
		this.capacidade = tamanho_lista;
	}

	/**
	 * Metodo que insere um produto na tabela
	 *
	 * @param codigo 	-> codigo do produto
	 * @param preco 	-> preco do produto
	 * @param descricao -> descricao do produto
	 * 
	 * @return inteiro	-> 0 - Inseriu
	 * 					-> 1 - Nao inseriu, tabela cheia
	 * 					-> 2 - Nao inseriu, ja havia um produto com esse codigo
	 */
	public int inserirProduto(int codigo, double preco, String descricao){
		if(produtos.size() <= capacidade) {
			for(Produto prod: produtos){
				if(prod.getCodigo() == codigo) { return 2; }
			}
			
			produtos.add(new Produto(codigo, preco, descricao));
			return 0;
		}
		return 1;
	}
	
	
	/**
	 * Metodo que retorna as informacoes do produto
	 * 
	 * @return Array de Produtos
	 * 					-> Se nao houver produtos retorna um array vazio
	 */
	public ArrayList <Produto> listarProdutos() {
		return produtos;
	}
	
	/**
	 * Metodo que retorna o preco de um produto dado seu codigo. 
	 *
	 * @param codigo 	-> codigo do produto, do qual se quer o preco
	 * @return preco 	-> preco do produto do codigo informado. 
	 * 					-> Se o produto nao for encontrado, retorna -1
	 */
	public double precoProduto(int codigo) {
		for(Produto prod: produtos){
			if(prod.getCodigo() == codigo) { return prod.getPreco(); }
		}
		return -1;
	}
	
	/**
	 * Metodo que retorna os produtos dentro da faixa de preco. 
	 *
	 * @param min 					-> valor minimo do preco
	 * @param max 					-> valor maximo do preco
	 * @return Array de Produtos	-> array ordenado por preco 
	 * 					-> Se nao houver produtos retorna um array vazio
	 */
	public ArrayList <Produto> filtrarPreco(double min, double max) {
		ArrayList <Produto> produtos_faixa = new ArrayList <Produto>();
		for(Produto prod: produtos){
			if(prod.getPreco() >= min && prod.getPreco() <= max) { produtos_faixa.add(prod); }
		}
		
		if(produtos_faixa.size() > 0) {
			Collections.sort(produtos_faixa, Comparator.comparingDouble(Produto ::getPreco));
		}
		return produtos_faixa;
	}
}
