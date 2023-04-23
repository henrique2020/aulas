package entidades;

public class ControleDeBonificacoes {
	
	private double totalDeBonificacoes = 0;

    public void registra(Funcionario funcionario) {              // m�todo polim�rfico
        this.totalDeBonificacoes += funcionario.getBonificacao();
    }

    public double getTotalDeBonificacoes() {
        return this.totalDeBonificacoes;
    }
}
