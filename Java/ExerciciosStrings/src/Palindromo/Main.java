package Palindromo;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Digite O palindromo que deseja testar");
        String palindromo = scan.nextLine();
        String palindromo_invertido = new StringBuffer(palindromo).reverse().toString();

        System.out.println("Verificando com espaços");
        if(palindromo.equalsIgnoreCase(palindromo_invertido)){ 
            System.out.println("É palindromo");
        } else{ 
            System.out.println("Não é palindromo");
        }

        System.out.println();

        palindromo = palindromo.replaceAll(" ", "");
        palindromo_invertido = new StringBuffer(palindromo).reverse().toString();
        System.out.println("Verificando sem espaços");
        if(palindromo.equalsIgnoreCase(palindromo_invertido)){ 
            System.out.println("É palindromo");
        } else{ 
            System.out.println("Não é palindromo");
        }
        
        scan.close();
    }
}