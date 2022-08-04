package ex2;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class Fibonacci {
    public int[] Sequencia(int tamanho){
        int[] seq_fibonacci = new int[tamanho];
        int n1 = 0, n2 = 1;
        seq_fibonacci[0] = n1;
        for (int i = 1; i < tamanho; i++) {
            int fib = n1 + n2;
            n1 = n2;
            n2 = fib;
            seq_fibonacci[i] = fib; 
        }
        return seq_fibonacci;
    }
    public static void main(String[] args) throws IOException {
        Fibonacci fib = new Fibonacci();
        InputStreamReader ir = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(ir);

        System.out.print("Digite a posição que deseja descobrir: ");
        int posicao = Integer.parseInt(in.readLine());     
        
        int num = fib.Sequencia(posicao)[posicao-1];
        
        System.out.printf("O %d° número da sequência de Fibonacci é %d\n", posicao, num);
        
        in.close();
        ir.close();
    }
}
