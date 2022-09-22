package model;

public class Data {
	private int dia;
	private int mês;
	private int ano;
	
    //Object
	public Data(int dia, int mês, int ano) {
		this.dia = dia;
		this.mês = mês;
		this.ano = ano;
	}

	//Getters and Setters
	public int getDia() {
		return dia;
	}

	public void setDia(int dia) {
		this.dia = dia;
	}

	public int getMês() {
		return mês;
	}

	public void setMês(int mês) {
		this.mês = mês;
	}

	public int getAno() {
		return ano;
	}

	public void setAno(int ano) {
		this.ano = ano;
	}

}
