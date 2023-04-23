package model;

public class Funcionario {
    
	private int id;
	private String nome;
	private String senha;
	
	//Object
	public Funcionario() {}

	public Funcionario(int id, String nome, String senha) {
		this.id = id;
		this.nome = nome;
		this.senha = senha;
	}

	//Getters and Setters
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getSenha() {
		return senha;
	}

	public void setSenh(String senha) {
		this.senha = senha;
	}
}
