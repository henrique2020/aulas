package entidades;

public class ControleDeBonificacoes {
	
	private double totalDeBonificacoes = 0;

    public void registra(Funcionario funcionario) {              // método polimórfico
        this.totalDeBonificacoes += funcionario.getBonificacao();
    }

    public double getTotalDeBonificacoes() {
        return this.totalDeBonificacoes;
    }
}
