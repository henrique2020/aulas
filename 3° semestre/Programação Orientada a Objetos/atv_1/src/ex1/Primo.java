package ex1;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import functions.NumeroPrimo;

public class Primo {
    
    public static void main(String[] args) throws IOException {
        NumeroPrimo primo = new NumeroPrimo();
        InputStreamReader ir = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(ir);
        
        System.out.print("Digite o número que deseja verificar: ");
        int num = Integer.parseInt(in.readLine());
        

        if(primo.verificaPrimo(num)){
            System.out.printf("%d é primo", num);
        }
        else{
            System.out.printf("%d não é primo", num);
        }

        in.close();
        ir.close();
    }
}
