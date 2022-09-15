package banco;

import model.Cliente;

public class TesteArrays {

	public static void main(String[] args) {
		
		int[] vet = new int[10];
		int[] outro = vet;	//Cria uma referencia a vet
		vet[0] = 10;
		System.out.println(vet[0]);
		outro[0] *= 2;
		System.out.println(vet[0]);

		Cliente[] listaClientes = new Cliente[5];
		
		for (int i = 0; i < listaClientes.length; i++) {
			listaClientes[i] = new Cliente("");
		}
		
		listaClientes[0].setNome("Henrique");
		listaClientes[0].setEndereco("Vila Rica - Feliz");
		listaClientes[0].setCpf("01234567890");
		
		listaClientes[1].setNome("Augusto");
		
		
		for (int i = 0; i < listaClientes.length; i++) {
			System.out.println(listaClientes[i].getNome()+" | "+listaClientes[i].getEndereco()+" | "+listaClientes[i].getCpf());
		}
	}

}
