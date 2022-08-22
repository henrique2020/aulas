package ContarPalavras;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Digite uma frase");
        String frase = scan.nextLine();
        String[] palavras = frase.toLowerCase().split(" ");
        int tamanho = palavras.length;

        String[] palavras_unicas = new String[tamanho];
        int[] contagem = new int[tamanho];

        int position = 0;
        for (int i = 0, k = 0; i < tamanho; i++) {
            if(Arrays.asList(palavras_unicas).contains(palavras[i])){
                position = Arrays.asList(palavras_unicas).indexOf(palavras[i]);
                contagem[position] += 1;
            } else {
                palavras_unicas[k] = palavras[i];
                contagem[k] = 1;
                k++;
            }
        }

        int max = Arrays.stream(contagem).max().getAsInt();
        for (int i = 0; i < tamanho; i++){
            if(contagem[i] == max){
                System.out.printf("A palavra que mais apareceu foi '%s' repetindo %dx\n", palavras_unicas[i], contagem[i]);
            }
        }
        scan.close();
    }
}
