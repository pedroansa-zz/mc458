/**
 * Este arquivo pode ser usado como base para o seu codigo.
 * Preste especial atencao a funcao ja implementada "imprimeSaida". Esta função
 * deve ser usada para imprimir o resultado da execucao de cada algoritmo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Min(int a, int b, int c){
    int* lista = (int *)malloc(3 * sizeof(int));
    int menor = INFINITY;
    lista[0] = a;
    lista[1] = b;
    lista[2] = c;
    for (int i = 0; i < 3; i++){
        if(lista[i] < menor)
            menor = lista[i];
    }
    free(lista);
    return menor;
}

int MenorCaminho(int** M, int n, int m){
    int **R = (int **)malloc((n+1) * sizeof(int*));
    for(int i = 0; i < n+1; i++){
        R[i] = (int *)malloc((m+2) * sizeof(int));
    }

    for(int i = 0; i < m+2; i++){
        R[0][i] = 0;
    }
    for(int i = 0; i < n+1; i++){
        R[i][0] = INFINITY;
        R[i][m+1] =INFINITY;
    }

    for(int i = 1; i < n+1; i++){
        for(int j = 1; j < m+1; j++){
            //printf("%d\n", M[i-1][j-1]);
            R[i][j] = M[i-1][j-1] + Min(R[i-1][j], R[i-1][j-1], R[i-1][j+1]);
            //printf("%d\n", R[i][j]);
        }
    }
    //imprimeMatriz(R, n+1, m+2);
    int menor = INFINITY;
    for(int i = 1; i < m+1; i++){
        if(R[n][i] < menor)
            menor = R[n][i];
    }

    for(int i = 0; i < n+1; i++){
        free(R[i]);
    }
    free(R);

    return menor;

}
/**
 * Imprime o custo do caminho.
 */
void imprimeSaida(int custo) {
    printf("%d\n", custo);
}

void imprimeMatriz(int **M, int n, int m){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    int custo;

    int m, n;
    scanf("%d %d", &n, &m); // Aqui se salva as variáveis referentes ao número de linhas e de colunas

    int **P = malloc(n * sizeof(int *)); // Aqui se aloca espaço para um ponteiro de matriz e se salva os valores nele
    for (int i = 0; i < n; i++) {
        scanf("\n");
        P[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    //imprimeMatriz(P, n, m);

    custo = MenorCaminho(P,n,m);

    imprimeSaida(custo);
    
    for (int i = 0; i < n; i++) {
        free(P[i]);
    }
    free(P);
    return 0;
}