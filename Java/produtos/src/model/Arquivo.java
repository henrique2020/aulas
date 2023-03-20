package model;

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Arquivo {
	private File arquivo;

	/**
	 * Construtor -> inicializa uma Arquivo
	 * 
	 * @param caminho -> Arquivo de onde serao lidos os dados
	 */
	public Arquivo(String caminho) {
		this.arquivo = new File(caminho);
		System.out.println(arquivo);
	}

	/**
	 * Metodo que recupera os produtos salvos no arquivo
	 * 
	 * @return Array de Produtos
	 *         -> Se nao houver produtos retorna um array vazio
	 * 
	 * @throws IOException
	 */
	public ArrayList<Produto> Load() throws IOException {
		FileReader fr = new FileReader(arquivo);
		BufferedReader br = new BufferedReader(fr);

		ArrayList<Produto> produtos = new ArrayList<Produto>();
		String linha, descricao;
		int codigo;
		double preco;
		while ((linha = br.readLine()) != null) {
			codigo = Integer.parseInt(linha);
			preco = Double.parseDouble(br.readLine());
			descricao = br.readLine();
			produtos.add(new Produto(codigo, preco, descricao));

			br.readLine(); // Linha vazia
		}

		br.close();
		fr.close();
		return produtos;
	}

	/**
	 * Metodo que salva os produtos no arquivo
	 * 
	 * @param Array de Produtos
	 * 
	 * @throws IOException
	 */
	public void Save(ArrayList<Produto> produtos) throws IOException {
		FileWriter fw = new FileWriter(arquivo);
		BufferedWriter bf = new BufferedWriter(fw);

		for (Produto tempProduto : produtos) {
			bf.write(Integer.toString(tempProduto.getCodigo()) + '\n');
			bf.write(Double.toString(tempProduto.getPreco()) + '\n');
			bf.write(tempProduto.getDescricao() + '\n');
			bf.newLine();
		}

		bf.flush();
		bf.close();
		fw.close();
	}

}