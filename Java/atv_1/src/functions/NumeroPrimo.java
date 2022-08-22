package functions;

public class NumeroPrimo {
	
	public boolean verificaPrimo(int num) {
        if(num < 2){
            return false;
        }
        else if (num == 2) {
            return true;
        } else {
            for (int i = 2; i < (num+1)/2; i++) {
                if(num%i == 0){
                    return false;
                }
            }
            return true;  
        }
    }
	
}
