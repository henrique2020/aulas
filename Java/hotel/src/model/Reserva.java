package model;

import java.time.temporal.ChronoUnit;

public class Reserva {
	private Funcionario funcionario;
	private Cliente cliente;
	private Quarto quarto;
	private Data data_de_entrada;
	private Data data_de_saida;
    private String metodo_pagamento;

    //Object
	public Reserva(Funcionario funcionario, Cliente cliente, Quarto quarto, Data data_de_entrada, Data data_de_saida, String metodo_pagamento) {
		this.funcionario = funcionario;
		this.cliente = cliente;
		this.quarto = quarto;
		this.data_de_entrada = data_de_entrada;
		this.data_de_saida = data_de_saida;
		this.metodo_pagamento = metodo_pagamento;
	}

	//Getters and Setters
	public Funcionario getFuncionario() {
		return funcionario;
	}

	public void setFuncionario(Funcionario funcionario) {
		this.funcionario = funcionario;
	}

	public Cliente getCliente() {
		return cliente;
	}

	public void setCliente(Cliente cliente) {
		this.cliente = cliente;
	}

	public Quarto getQuarto() {
		return quarto;
	}

	public void setQuarto(Quarto quarto) {
		this.quarto = quarto;
	}

	public Data getData_de_entrada() {
		return data_de_entrada;
	}

	public void setData_de_entrada(Data data_de_entrada) {
		this.data_de_entrada = data_de_entrada;
	}

	public Data getData_de_saida() {
		return data_de_saida;
	}

	public void setData_de_saida(Data data_de_saida) {
		this.data_de_saida = data_de_saida;
	}

	public String getMetodo_pagamento() {
		return metodo_pagamento;
	}

	public void setMetodo_pagamento(String metodo_pagamento) {
		this.metodo_pagamento = metodo_pagamento;
	}

	public int getTempo() {
		return (int) ChronoUnit.DAYS.between(data_de_entrada.getData().toInstant(),  data_de_saida.getData().toInstant());
	}
	
	public boolean verificaDisponibilidade(Data entrada, Data saida) {
		if (entrada.getData().compareTo(data_de_entrada.getData()) >= 0 && entrada.getData().compareTo(data_de_saida.getData()) <= 0) {
			return false;
		}
		else if (saida.getData().compareTo(data_de_entrada.getData()) >= 0 && saida.getData().compareTo(data_de_saida.getData()) <= 0) {
			return false;
		}
		else if (entrada.getData().compareTo(data_de_entrada.getData()) <= 0 && saida.getData().compareTo(data_de_saida.getData()) >= 0) {
			return false;
		}
		return true;
	}
	
}
