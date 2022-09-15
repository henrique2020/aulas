package api;

import java.util.Calendar;

public class Data {

	private int dia;
	private int mes;
	private int ano;

	
	//Instancia
	public Data() {
		Calendar calendario = Calendar.getInstance();
		this.dia = calendario.get(Calendar.DATE);
		this.mes = calendario.get(Calendar.MONTH) + 1;
		this.ano = calendario.get(Calendar.YEAR);
	}
	
	public Data(int dia, int mes, int ano) {
		super();
		this.dia = dia;
		this.mes = mes;
		this.ano = ano;
	}
	
	
	//Metodos
	public int getDia() {
		return dia;
	}
	public void setDia(int dia) {
		this.dia = dia;
	}
	
	public int getMes() {
		return mes;
	}
	public void setMes(int mes) {
		this.mes = mes;
	}
	
	public int getAno() {
		return ano;
	}
	public void setAno(int ano) {
		this.ano = ano;
	}

	public String getData() {
		return this.dia+"/"+this.mes+"/"+this.ano;
	}
}
