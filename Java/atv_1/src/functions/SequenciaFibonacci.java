package functions;

public class SequenciaFibonacci {
	
	public int[] geraSequencia(int tamanho){
        int[] seq_fibonacci = new int[tamanho];
        int n1 = 0, n2 = 1;
        seq_fibonacci[0] = n1;
        for (int i = 1; i < tamanho; i++) {
            int fib = n1 + n2;
            n1 = n2;
            n2 = fib;
            seq_fibonacci[i] = fib; 
        }
        return seq_fibonacci;
    }

}
