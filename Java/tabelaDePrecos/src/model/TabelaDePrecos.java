package model;

/**
 * Classe que implementa uma tabela de pre�os de produtos.
 *
 * @author Marcos
 * @version 13/04/2021
 */

public class TabelaDePrecos {

	private Produto[] produtos ;
	private int tamanho ;     // quantidade de produtos na tabela
	private int capacidade ;  // n�mero m�ximo de produtos (capacidade do array)

	/**
	 * Construtor que inicializa uma TabelaDePrecos com uma capacidade espec�fica 
	 *
	 * @param capacidade A capacidade m�xima da tabela
	 */
	public TabelaDePrecos(int capacidade)
	{
		// completar
	}

	/**
	 * M�todo que retorna o pre�o de um produto dado seu c�digo. 
	 *
	 * @param codigo O c�digo do produto do qual se quer o pre�o
	 * @return O pre�o do produto com o c�digo informado. Se o produto n�o �
	 * encontrado, retorna -1
	 */
	public double getPrecoDoProduto(int codigo)
	{
		// completar
		return 0;
	}

	/**
	 * M�todo que insere um produto na tabela
	 *
	 * @param codigo O c�digo do produto
	 * @param preco O pre�o do produto
	 * @return Um n�mero inteiro informando o status da inser��o: 0 - inser��o
	 * aconteceu sem problemas; 1- inser��o n�o aconteceu porque a tabela estava cheia;
	 * 2- inser��o n�o aconteceu porque j� havia um produto na tabela com o c�digo
	 * informado
	 */
	public int inserirProduto(int codigo, double preco, String descricao)
	{
		// completar
		return 0;
	}
	
	/**
	 * M�todo que insere um produto na tabela
	 *
	 * @param produto O objeto Produto que ser� inclu�do na tabela
	 * @return Um n�mero inteiro informando o status da inser��o: 0 - inser��o
	 * aconteceu sem problemas; 1- inser��o n�o aconteceu porque a tabela estava cheia;
	 * 2- inser��o n�o aconteceu porque j� havia um produto na tabela com o c�digo
	 * informado
	 */
	public  int  inserirProduto(Produto produto) // sobrecarga de m�todo - method overloading
										
	{
		// completar
		return 0;
	}
	
	/**
	 * M�todo que remove um produto na tabela
	 *
	 * @param codigo O c�digo do produto que deve ser removido
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
