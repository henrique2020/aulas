package model;

/**
 * Classe que implementa uma tabela de preços de produtos.
 *
 * @author Marcos
 * @version 13/04/2021
 */

public class TabelaDePrecos {

	private Produto[] produtos ;
	private int tamanho ;     // quantidade de produtos na tabela
	private int capacidade ;  // número máximo de produtos (capacidade do array)

	/**
	 * Construtor que inicializa uma TabelaDePrecos com uma capacidade específica 
	 *
	 * @param capacidade A capacidade máxima da tabela
	 */
	public TabelaDePrecos(int capacidade)
	{
		// completar
	}

	/**
	 * Método que retorna o preço de um produto dado seu código. 
	 *
	 * @param codigo O código do produto do qual se quer o preço
	 * @return O preço do produto com o código informado. Se o produto não é
	 * encontrado, retorna -1
	 */
	public double getPrecoDoProduto(int codigo)
	{
		// completar
		return 0;
	}

	/**
	 * Método que insere um produto na tabela
	 *
	 * @param codigo O código do produto
	 * @param preco O preço do produto
	 * @return Um número inteiro informando o status da inserção: 0 - inserção
	 * aconteceu sem problemas; 1- inserção não aconteceu porque a tabela estava cheia;
	 * 2- inserção não aconteceu porque já havia um produto na tabela com o código
	 * informado
	 */
	public int inserirProduto(int codigo, double preco, String descricao)
	{
		// completar
		return 0;
	}
	
	/**
	 * Método que insere um produto na tabela
	 *
	 * @param produto O objeto Produto que será incluído na tabela
	 * @return Um número inteiro informando o status da inserção: 0 - inserção
	 * aconteceu sem problemas; 1- inserção não aconteceu porque a tabela estava cheia;
	 * 2- inserção não aconteceu porque já havia um produto na tabela com o código
	 * informado
	 */
	public  int  inserirProduto(Produto produto) // sobrecarga de método - method overloading
										
	{
		// completar
		return 0;
	}
	
	/**
	 * Método que remove um produto na tabela
	 *
	 * @param codigo O código do produto que deve ser removido
	 */
	public void removerProduto(int codigo)
	{
		// vamos implementar mais tarde
	}
	
	
	public Produto[] pesquisaPorPalavraChave(String chave)
	{
		Produto[] temp = new Produto[tamanho];
			
		
		return temp;
	}

}
