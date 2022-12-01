package model;

public class Produto {
	private int codigo;
	private double preco;
	private String descricao;
	
	public Produto(int codigo, double preco, String descricao) {
		this.codigo = codigo;
		this.preco = preco;
		this.descricao = descricao;
	}
	
	public int getCodigo() {
		return codigo;
	}
	public void setCodigo(int codigo) {
		this.codigo = codigo;
	}
	public double getPreco() {
		return preco;
	}
	public void setPreco(double preco) {
		this.preco = preco;
	}
	public String getDescricao() {
		return descricao;
	}
	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
}
