package ContarEspacos;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Digite uma frase para saber quantos espaços tem nela");
        String frase = scan.nextLine();
        int espacos = 0;
        for (char caracter : frase.toCharArray()) {
            if(caracter == ' '){
                espacos++;
            }
        }
        System.out.printf("Essa frase possui %d espaços\n", espacos);
        scan.close();
    }
}
