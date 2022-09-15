package api;

public class Pessoa {
	
	private String nome;
	private String cpf;
	private Data nascimento;
	private Endereco endereco;
	private int idade;
	
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public String getCpf() {
		return cpf;
	}
	public void setCpf(String cpf) {
		this.cpf = cpf;
	}
	
	public Data getNascimento() {
		return nascimento;
	}
	public void setNascimento(Data nascimento) {
		this.nascimento = nascimento;
	}
	
	public Endereco getEndereco() {
		return endereco;
	}
	public void setEndereco(Endereco endereco) {
		this.endereco = endereco;
	}
	
	public int getIdade() {
		return idade;
	}
	public void setIdade(int idade) {
		this.idade = idade;
	}
}
