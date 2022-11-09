package entidades;

public class Funcionario extends Pessoa{
	
	protected double salario;
	
	public Funcionario(String nome, String cpf, double salario) {
		super(nome, cpf);
		this.salario = salario;
	}

	public double getSalario() {
		return salario;
	}

	public void setSalario(double salario) {
		this.salario = salario;
	}
	
	public double getBonificacao() {
		this.getBonificacao() + 1000;
	}
}
