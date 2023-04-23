package model;

public class Impressora extends Produto {

    public Impressora(int codigo, double preco, String descricao) {
        super(codigo, preco, descricao);
    }

    @Override
    public double correcaoMonetaria(double preco) {
        return preco * 1.17;
    }
}