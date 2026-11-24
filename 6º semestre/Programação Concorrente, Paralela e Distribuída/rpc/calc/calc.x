struct args{
    float op1;
    float op2;
};

program calcprogram{
    version calcversion{
        float adicao(struct args) = 1;
        float subtracao(struct args) = 2;
        float mutiplicacao(struct args) = 3;
        float divisao(struct args) = 4;
    }=1;
}=0x21000000;