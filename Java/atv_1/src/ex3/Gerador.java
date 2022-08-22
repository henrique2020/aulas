package ex3;

import java.util.Scanner;
import functions.SequenciaFibonacci;
import functions.NumeroPrimo;

public class Gerador {

    public static void main(String[] args) {
    	SequenciaFibonacci fib = new SequenciaFibonacci();
        NumeroPrimo primo = new NumeroPrimo();
        Scanner scan = new Scanner(System.in);
        
        System.out.println("Defina o tamanho da sequência de Fibonacci");
        int tamanho = scan.nextInt();

        int[] seq_fibonacci = fib.geraSequencia(tamanho);

        for (int i : seq_fibonacci) {
            
            if(primo.verificaPrimo(i)){
                System.out.printf("O número %d é primo", i);
            }
            else{
                System.out.printf("O número %d não é primo", i);
            }
            System.out.println();
        }
        
        scan.close();
    }
}
