#include "TG.h"
#include <limits.h>

//MENOR CAMINHO ENTRE DOIS NOS EM UM GRAFO COM PESOS.

int max(TG*g){
    int a = 0;
    TG* p = g;
    while (p) {
        if (p->id_no>a)a=p->id_no;
        p = p->prox_no;
    }
    return a;
}

void teste(TG* g, int k_atual, int k,int dest, int atual, int caminho_atual,int* caminho,int* visitados,int* menor_k){
    visitados[atual] = 1;
    k_atual++;
    if(k_atual> k)caminho_atual = INT_MAX;
    if(atual == dest){
        if (caminho_atual < *caminho){
            *menor_k = k_atual;
            *caminho = caminho_atual;
        }
    }
    else{
        TG* a = TG_busca_no(g,atual);
        TVIZ* viz = a->prim_viz;
        while(viz){
            if(!visitados[viz->id_viz]){
                teste(g, k_atual,k,dest,viz->id_viz,caminho_atual+viz->custo,caminho,visitados,menor_k);
            }
            viz = viz->prox_viz;
        }
    }
    visitados[atual] = 0;
}

int mdk(TG *g, int origem, int destino, int k, int *tam_real_caminho){
    if(!g){
        *tam_real_caminho = INT_MAX;
        return INT_MAX;
    }
    int* visitados = calloc(max(g)+1,sizeof(int));
    int* menor_k = malloc(sizeof(int));
    *menor_k = INT_MAX;
    *tam_real_caminho= INT_MAX;
    teste(g,-1,k,destino,origem,0,tam_real_caminho,visitados,menor_k);
    int resultado = *tam_real_caminho;
    *tam_real_caminho = *menor_k;
    free(menor_k);
    free(visitados);
    return resultado;
}







int main(void){
  TG *g = TG_inicializa();
  int n;
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
  }while(1);
  
  int m, custo;
  do{
    scanf("%d%d%d", &n, &m, &custo);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m, custo);
  }while(1);
  TG_imprime(g);
  
  int k;
  scanf("%d%d%d", &n, &m, &k);


  int tam_real = 0;
  custo = mdk(g, n, m, k, &tam_real);
  printf("no %d alcanca o no %d em %d arestas: %d (%d)\n", n, m, k, custo, tam_real);

  TG_libera(g);
  return 0;
}