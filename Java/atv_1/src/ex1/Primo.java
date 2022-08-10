package ex1;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class Primo {
    public boolean Verificador(int num) {
        if(num < 2){
            return false;
        }
        else if (num == 2) {
            return true;
        } else {
            for (int i = 2; i < (int) (num+1)/2; i++) {
                if(num%i == 0){
                    return false;
                }
            }
            return true;  
        }
    }
    public static void main(String[] args) throws IOException {
        Primo primo = new Primo();
        InputStreamReader ir = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(ir);
        
        System.out.print("Digite o número que deseja verificar: ");
        int num = Integer.parseInt(in.readLine());
        

        if(primo.Verificador(num)){
            System.out.printf("%d é primo", num);
        }
        else{
            System.out.printf("%d não é primo", num);
        }

        in.close();
        ir.close();
    }
}
