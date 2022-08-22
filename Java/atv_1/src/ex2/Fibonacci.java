package ex2;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import functions.SequenciaFibonacci;

public class Fibonacci {
    
    public static void main(String[] args) throws IOException {
    	SequenciaFibonacci fib = new SequenciaFibonacci();
        InputStreamReader ir = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(ir);

        System.out.print("Digite a posição que deseja descobrir: ");
        int posicao = Integer.parseInt(in.readLine());     
        
        int num = fib.geraSequencia(posicao)[posicao-1];
        
        System.out.printf("O %d° número da sequência de Fibonacci é %d\n", posicao, num);
        
        in.close();
        ir.close();
    }
}
