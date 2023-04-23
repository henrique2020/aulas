package banco;

import model.Cliente;
import model.ContaCorrente;

public class TesteDoBanco {

	public static void main(String[] args) {
		
		Cliente cli1, cli2;
		
		cli1 = new Cliente("");
		cli2 = new Cliente("");
		
		cli1.setNome("marcos");
		cli1.setCpf("3245234");
		
		cli2.setNome("maria");

		
		ContaCorrente conta1 = new ContaCorrente(cli1);
		ContaCorrente conta2 = new ContaCorrente(cli2);
		
		conta1.depositar(7654);
		System.out.println("saldo : "+conta1.getSaldo());
		conta1.depositar(10000);
		System.out.println("saldo : "+conta1.getSaldo());
		
		conta2.depositar(500);
		System.out.println("saldo : "+conta2.getSaldo());
		
		
		
				

	}

}
