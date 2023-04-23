package aula_2;

import java.io.IOException;
import java.util.Scanner;

public class atividade_4 {

    public static void main(TetseString[] args) throws IOException {
    	Scanner scan = new Scanner(System.in);
    	
    	System.out.println("Digite algo:");
    	System.out.println(scan.nextLine().isBlank());
    	
    	scan.close();
    }

}