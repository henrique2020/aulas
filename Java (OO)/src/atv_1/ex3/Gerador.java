package ex3;

import java.util.Scanner;
import ex1.Primo;
import ex2.Fibonacci;

public class Gerador {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Defina o tamanho da sequência de Fibonacci");
        int tamanho = scan.nextInt();

        Fibonacci fib = new Fibonacci();
        int[] seq_fibonacci = fib.Sequencia(tamanho);

        for (int i : seq_fibonacci) {
            Primo primo = new Primo();
            if(primo.Verificador(i)){
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
