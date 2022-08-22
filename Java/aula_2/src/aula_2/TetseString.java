package aula_2;

import java.util.Scanner;

public class TetseString {

	public static void main(java.lang.String[] args) {
		Scanner scan = new Scanner(System.in);

		System.out.print("Digite uma frase: ");
		String frase = scan.nextLine();
		
		int espacos = 0;
		for (char c : frase.toCharArray()) {
			if(c == ' ') {
				espacos++;
			}
		}
			
		System.out.println(espacos);
		scan.close();
	}

}
