package entidades;

public class Cliente extends Pessoa {
	
	private String situacaoDeCredito;

	public Cliente(String nome, String cpf) {
		super(nome, cpf);
	}

	public String getSituacaoDeCredito() {
		return situacaoDeCredito;
	}

	public void setSituacaoDeCredito(String situacaoDeCredito) {
		this.situacaoDeCredito = situacaoDeCredito;
	}	
}
