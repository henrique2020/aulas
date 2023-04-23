package model;

public class Quarto {
    
	private int numero;
    private int andar;
    private float diaria;
	private String nome;
    private String tipo;
    
    //Object
	public Quarto() {}

	public Quarto(int numero, int andar, float diaria, String nome, String tipo) {
		this.numero = numero;
		this.andar = andar;
		this.diaria = diaria;
		this.nome = nome;
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

	public float getDiaria() {
		return diaria;
	}

	public void setDiaria(float diaria) {
		this.diaria = diaria;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getTipo() {
		return tipo;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
	}
    
}
