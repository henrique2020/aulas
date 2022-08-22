package ContarComprimento;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Digite uma frase");
        String frase = scan.nextLine();

        System.out.printf("Utilizando 'length()' - Essa frase possui %d caracteres\n", frase.length());        
        scan.close();
    }
}