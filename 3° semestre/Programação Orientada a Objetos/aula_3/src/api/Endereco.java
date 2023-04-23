package api;

public class Endereco {
	
	private String rua;
	private String numero;
	private String compelmento;
	private String cep;
	private String cidade;
	private String estado;
	
	
	//Instancias
	public Endereco() {
	}
	
	public Endereco(String rua, String numero, String compelmento, String cep, String cidade, String estado) {
		this.rua = rua;
		this.numero = numero;
		this.compelmento = compelmento;
		this.cep = cep;
		this.cidade = cidade;
		this.estado = estado;
	}

	
	//Metodos
	public String getRua() {
		return rua;
	}
	public void setRua(String rua) {
		this.rua = rua;
	}

	public String getNumero() {
		return numero;
	}
	public void setNumero(String numero) {
		this.numero = numero;
	}

	public String getCompelmento() {
		return compelmento;
	}
	public void setCompelmento(String compelmento) {
		this.compelmento = compelmento;
	}

	public String getCep() {
		return cep;
	}
	public void setCep(String cep) {
		this.cep = cep;
	}

	public String getCidade() {
		return cidade;
	}
	public void setCidade(String cidade) {
		this.cidade = cidade;
	}

	public String getEstado() {
		return estado;
	}
	public void setEstado(String estado) {
		this.estado = estado;
	}
}
