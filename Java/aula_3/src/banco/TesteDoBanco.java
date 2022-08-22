package banco;

public class TesteDoBanco {

	public static void main(String[] args) {
		
		ContaCorrente conta1 = new ContaCorrente();
		ContaCorrente conta2 = new ContaCorrente();
		
		conta1.depositar(7654);
		System.out.println("saldo : "+conta1.saldo);
		conta1.depositar(10000);
		System.out.println("saldo : "+conta1.saldo);
		
		conta2.depositar(500);
		System.out.println("saldo : "+conta2.saldo);
		
		
		
		Cliente cli1, cli2;
		
		cli1 = new Cliente();
		cli2 = new Cliente();
		
		cli1.nome = "marcos";
		cli1.cpf = "3245234";
		
		cli2.nome = "maria";
		

	}

}
