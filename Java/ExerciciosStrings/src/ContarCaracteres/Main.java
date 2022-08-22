package ContarCaracteres;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Digite uma frase");
        String frase = scan.nextLine().toUpperCase();

        System.out.println("Digite a letra que gostaria de contar");
        char letra = scan.nextLine().toUpperCase().charAt(0);

        int repeticoes = 0;
        for (char caracter : frase.toCharArray()) {
            if(caracter == letra){
                repeticoes++;
            }
        }
        System.out.printf("Essa frase possui %d letras %c\n", repeticoes, letra);
        scan.close();
    }
}