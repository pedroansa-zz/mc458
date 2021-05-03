/**
 * Este arquivo pode ser usado como base para o seu codigo.
 * Preste especial atencao a funcao ja implementada "imprimeSaida". Esta função
 * deve ser usada para imprimir o resultado da execucao de cada algoritmo.
 */

#include <stdio.h>

/**
 * Imprime "S" se emBalanco for maior que 0, e "N" caso contrario.
 */
void imprimeSaida(int emBalanco) {
	printf("%s\n", (emBalanco ? "S" : "N"));
}

typedef struct {
    int bolval;
    int intVal;
} Tuple;

Tuple CreateTuple(int bol, int val){
    Tuple tuple;
    tuple.bolval = bol;
    tuple.intVal = val;
    return tuple;
}

Tuple equilibrada(){
    scanf("\n");
    int pd, pe, dd, de, pt;
    int eq = 1;
    Tuple tuple;
    scanf(" %d %d %d %d", &pd, &dd, &pe, &de);

    if(pd != 0 && pe != 0){
        pt = pd + pe;
        if(pd * dd != pe*de){
            eq = 0;
        }
        return CreateTuple(eq, pt);
    }

    if(pd == 0){
        tuple = equilibrada();
        if (tuple.bolval == 0)
            return tuple;
        pd = tuple.intVal;
    }

    if(pe == 0){
        tuple = equilibrada();
        if (tuple.bolval == 0)
            return tuple;
        pe = tuple.intVal;
    }

    if (pd*dd != pe * de){
        eq = 0;
    }

    return CreateTuple(eq, pe+pd);
} 

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d",&n); // Aqui se recebe um inteiro n indicando a quantidade de linhas

    int emBalanco;
    int pt;
    Tuple tuple;
    tuple = equilibrada();
    imprimeSaida(tuple.bolval) ;

	return 0;
}
