package model;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class Data {
	Calendar data;
	
    //Object
	public Data(int dia, int mes, int ano) {
		data = new GregorianCalendar(ano, mes, dia);
	}

	public Calendar getData() {
		return data;
	}
	
	//Getters and Setters
	public int getDia() {
		return data.get(Calendar.DAY_OF_MONTH);
	}

	public void setDia(int dia) {
		this.data.set(Calendar.DAY_OF_MONTH, dia);
	}

	public int getMes() {
		return data.get(Calendar.MONTH+1);
	}

	public void setMes(int mes) {
		this.data.set(Calendar.MONTH, mes);
	}

	public int getAno() {
		return data.get(Calendar.YEAR);
	}

	public void setAno(int ano) {
		this.data.set(Calendar.YEAR, ano);
	}
}