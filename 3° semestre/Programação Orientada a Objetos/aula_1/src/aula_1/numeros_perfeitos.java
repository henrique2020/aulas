package aula_1;

public class numeros_perfeitos {
	
	public static void main(String[] args) {
		int count = 0;
		int num = 1;
		//A ideia era ser o 5 primeiros, porém o 5° é mt grande
		while(count < 4) {
			//boolean perfeito = true;
			int soma = 0;
			num++;
			for(int div = 1; div <= (int) num/2; div++) {
				if(num%div == 0) {
					soma+=div;
				}
			}
			if(soma == num) {
				System.out.println("N perfeito: " + num);
				//System.out.printf("N perfeito: %d\n", num);
				count++;
			}
		}
	}
}