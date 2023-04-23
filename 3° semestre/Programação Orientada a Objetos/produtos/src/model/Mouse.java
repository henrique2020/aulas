package model;

public class Mouse extends Produto {

    public Mouse(int codigo, double preco, String descricao) {
        super(codigo, preco, descricao);
    }

    @Override
    public double correcaoMonetaria(double preco) {
        return preco * 1.02;
    }
}
