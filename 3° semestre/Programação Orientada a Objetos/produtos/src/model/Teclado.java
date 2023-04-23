package model;

public class Teclado extends Produto {

    public Teclado(int codigo, double preco, String descricao) {
        super(codigo, preco, descricao);
    }

    @Override
    public double correcaoMonetaria(double preco) {
        return preco * 1.07;
    }
}