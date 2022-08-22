package banco;

public class ContaCorrente {

	int numero;
	double saldo;
	
	public void depositar(double valor) {
		
		saldo = saldo + valor;
		
	}
	
	
}
