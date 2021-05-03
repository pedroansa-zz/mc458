#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
  Funcao para validar seus algoritmos.
  Retorna 1 se a resposta estiver correta, 0 caso contrario.
  Caso a resposta seja incorreta, imprime tambem a resposta fornecida
  e a resposta esperada.
  Parametros:
  const double *v: vetor com a instancia do problema.
  int n: numero de elementos do vetor v.
  int k: parametro k do problema (ver enunciado).
  const double *r: vetor encontrado pelo seu algoritmo, contendo nas k
  primeiras posicoes, os k menores elementos do vetor v em ordem
  crescente.
*/
int resposta_correta(const double *v, int n, int k, const double *r);

/*
  Implementacao do algoritmo QuickSort.
  Ordena o vetor passado como parametro em ordem crescente.
  Parametros:
  double *v: vetor com a instancia do problema.
  int n: numero de elementos do vetor v.
*/
void quick_sort(double *v, int n);

/*
  Utilize esta funcao para medir o tempo de execucao do seu programa.
  A primeira chamada retorna um valor indefinido. A partir da segunda
  chamada, o double retornado contem o tempo decorrido, em segundos,
  entre a chamada atual e a ultima chamada da funcao.

  Exemplo de uso para medir o tempo de execucao de uma funcao 'f()':

  tempo();
  f();
  double t = tempo();
*/
double tempo();

/*
  Escreve o vetor com os k menores elementos em um arquivo "kmin.out" criado. 
  (Obrigatório o uso dessa função no final do seu código para a correção).
  Parâmetros: 
  vector<double> &r: vetor encontrado pelo seu algoritmo.
*/
void kmin_to_file(double *r, int k);

void MinHeapfy(double *v, int n,int i){
  int e = 2*i;
  int d = (2*i)+1;
  int menor;
  double aux;
  if (e < n && v[e]<=v[i])
    menor = e;
  
  else
    menor = i;
  
  if (d < n && v[d]<=v[menor])
    menor = d;
  if (menor != i){
    aux = v[i];
    v[i] = v[menor];
    v[menor] = aux;
    MinHeapfy(v,n,menor);
  }
}

void BuildMinHeap(double *v, int n){
  for(int i = n/2; i > -1; i--)
    MinHeapfy(v,n,i);
}

double *metodo1(double *v, int k, int n){
  double anterior = -INFINITY;
  int aux;
  double *f = (double *)malloc(k * sizeof(double));

  for (int i = 0; i < k; i++){
    double imenor = INFINITY;
    for(int j = 0; j < n; j++){
      if(v[j] < imenor && v[j] >= anterior){
        imenor = v[j];
        aux = j;
      }
    }
    f[i] = imenor;
    v[aux] = INFINITY;
    anterior = imenor;
  }
  return f;
}

double *metodo2(double *v, int k, int n){
  quick_sort(v,n);

  double *f = (double *)malloc(k * sizeof(double));

  for (int i = 0; i < k; i++)
  {
    f[i] = v[i];
  }
  
  return f;
}

double *metodo3(double *v, int k, int n){
  BuildMinHeap(v,n);
  double *f = (double *)malloc(k * sizeof(double));
  for(int i = 0; i< k; i++){
    f[i] = v[0];
    v[0] = v[n-1-i];
    MinHeapfy(v,n-1-i,0);
  }
  
  return f;
}
int achark(double *v, double *(*f)(double *, int, int), double *(*g)(double *, int, int),int ini, int fim, int n){
  double t1, t2;
  double *copia1 = (double *)malloc(n * sizeof(double));
  double *copia2 = (double *)malloc(n * sizeof(double));
  double *resultado = (double *)malloc(n * sizeof(double));
  int aux = 0;
  for(int i = ini; i < fim; i++){
    for (int j = 0; j< n; j++){
    copia1[j] = v[j];
    copia2[j] = v[j];
  }
    tempo();
    resultado = f(copia1,i,n);
    t1 = tempo();
    free(resultado);
    tempo();
    resultado = g(copia2,i,n);
    t2 = tempo();
    free(resultado);
    //printf("%d %.6f %.6f\n",i, t1, t2);
    if(t1 > t2 + (0.001 * t2)){
      aux++;
    }
    else
      aux = 0;
      
    if(aux >= 5){
      free(copia1);
      free(copia2);
      return i;

    }

  }
  free(copia1);
  free(copia2);
  
}
int *metodo0(double *v, int k, int n){
   int k1, k2;
   int *R = (int *)malloc(2 * sizeof(int));
    
    k1 = achark(v,metodo1,metodo3,0,n,n);
    k2 = achark(v,metodo3,metodo2,500000,n,n);
    R[0] = k1;
    R[1] = k2;

    return R;
}

int main(int argc, char **argv){
  
  if(argc != 4){
    if(argc == 3 && argv[2][0] != '0'){
      fprintf(stderr, "Uso Método 0: ./kmin <arq> 0\n");
      return 1;
    }
    else if(argc != 3){
      fprintf(stderr, "Uso geral: ./kmin <arq> <metodo> <k>\n");
      return 1;
    }
  }

  char *nomearq = argv[1];
  char metodo = argv[2][0];
  int m = metodo - '0';
  int k;
  if(argc == 4) k = atoi(argv[3]);
	
  FILE *arq = fopen(nomearq, "r");
  int n, i;
  double *v;
  double *copia;
  double *f;		

  fscanf(arq, "%d", &n);
  v = (double *)malloc(n * sizeof(double));
  copia = (double *)malloc(n * sizeof(double));


  for (i = 0; i < n; i++) {
    fscanf(arq, "%lf", &v[i]);
    copia[i] = v[i];
  }

  fclose(arq);
  double t;
  tempo();
  if(m == 0){
    int *ai = metodo0(v,k,n);
    //Descomente aqui para imprimir o k1 e k2
    //printf("%d %d\n", ai[0], ai[1]);
    free(ai);
  }
  else if(m == 1){
    f = metodo1(v,k,n);
    kmin_to_file(f,k);
    free(f);
    
  }
  else if(m== 2){
    f = metodo2(v,k,n);
    kmin_to_file(f,k);
    free(f);
    
  }
  else {
    f = metodo3(v,k,n);
    kmin_to_file(f,k);
    free(f);
  
  }
  t = tempo();
  free(v);
  free(copia);
  /* Descomente para imprimir o tempo de execucao */
  printf("%.6f\n", t); 

  return 0;
}
