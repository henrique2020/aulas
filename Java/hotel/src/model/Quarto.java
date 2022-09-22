package model;

public class Quarto {
    
	private int numero;
    private int andar;
    private float valor;
    private String tipo;
    
    //Object
	public Quarto() {}

	public Quarto(int numero, int andar, float valor, String tipo) {
		this.numero = numero;
		this.andar = andar;
		this.valor = valor;
		this.tipo = tipo;
	}
	
	//Getters and Setters
	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public int getAndar() {
		return andar;
	}

	public void setAndar(int andar) {
		this.andar = andar;
	}

	public float getValor() {
		return valor;
	}

	public void setValor(float valor) {
		this.valor = valor;
	}

	public String getTipo() {
		return tipo;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
	}
    
}
