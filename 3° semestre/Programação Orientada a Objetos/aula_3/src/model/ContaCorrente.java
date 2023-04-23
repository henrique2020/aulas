package model;

public class ContaCorrente {

	//Variables
	private int numero;
	private double saldo;
	private Cliente titular;

	//Getters and Setters
	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public double getSaldo() {
		return saldo;
	}

	public void setSaldo(double saldo) {
		this.saldo = saldo;
	}

	public Cliente getTitular() {
		return titular;
	}

	public void setTitular(Cliente titular) {
		this.titular = titular;
	}

	
	//Functions
	public ContaCorrente(Cliente titular) {
		this.titular = titular;
	}
	
	public void ver_saldo(){
		System.out.printf("Saldo disponível: R$ %.2f\n", this.saldo);
	}

	public void depositar(double valor) {
		this.saldo += valor;
		ver_saldo();
	}

	public void sacar(double valor) {
		if ((this.saldo - valor) >= 0) {
			this.saldo -= valor;
		}
		else{
			System.out.println("Não é possível realizar a retirada de um valor que exceda o saldo dispinível");
		}
		ver_saldo();
	}
}