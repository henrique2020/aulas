package model;

public class Cliente {

	private int id;
	private String nome;
	private String cpf;
	private String telefone;
	private Data data_nascimento;
	private Endereco endereco;
	
	//Object
	public Cliente() {}

	public Cliente(int id, String nome, String cpf, String telefone) {
		this.id = id;
		this.nome = nome;
		this.cpf = cpf;
		this.telefone = telefone;
	}
	
	//Getters and Setters
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getnome() {
		return nome;
	}

	public void setnome(String nome) {
		this.nome = nome;
	}

	public String getCpf() {
		return cpf;
	}

	public void setCpf(String cpf) {
		this.cpf = cpf;
	}

	public Data getData_nascimento() {
		return data_nascimento;
	}

	public void setData_nascimento(Data data_nascimento) {
		this.data_nascimento = data_nascimento;
	}

	public Endereco getEndereco() {
		return endereco;
	}

	public void setEndereco(Endereco endereco) {
		this.endereco = endereco;
	}

	public String getTelefone() {
		return telefone;
	}

	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}
    
}
