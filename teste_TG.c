#include <stdlib.h>
#include <stdio.h>

typedef struct viz {
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
    int id_no;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

TG* TG_inicializa(){
    return NULL;
}


void TG_imprime(TG *g){
    while(g){
        printf("Vizinhos do No %d:\n", g->id_no);
        TVIZ *v = g->prim_viz;
        while(v){
            printf("%d ", v->id_viz);
            v = v->prox_viz;
        }
        printf("\n");
        g = g->prox_no;
    }
}

void TG_imp_rec(TG *g){
    if(g){
        printf("%d:\n", g->id_no);
        TVIZ *v = g->prim_viz;
        while(v){
            printf("%d ", v->id_viz);
            v = v->prox_viz;
        }
        TG_imp_rec(g->prox_no);
    }
}

void TG_libera_viz(TVIZ *v){
    while(v){
        TVIZ *temp = v;
        v = v->prox_viz;
        free(temp);
    }
}

void TG_libera_viz_rec(TVIZ *v){
    if(!v) return;
    TG_libera_viz_rec(v->prox_viz);
    free(v);
}

void TG_libera(TG *g){
    while(g){
        TG_libera_viz(g->prim_viz);
        TG *temp = g;
        g = g->prox_no;
        free(temp);
    }
}

void TG_libera_rec(TG *g){
    if(g){
        TG_libera_viz(g->prim_viz);
        TG_libera_rec(g ->prox_no);
        free(g);
    }
}

TG* TG_busca_no(TG* g, int x){
    if((!g) || (g->id_no == x)) return g;
    return(TG_busca_no(g->prox_no, x));
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2){
    TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
    if((!p1) || (!p2)) return NULL;
    TVIZ *resp = p1->prim_viz;
    while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
    return resp;
}

TG* TG_ins_no(TG *g, int x){
    TG *p = TG_busca_no(g, x);
    if(!p){
        p = (TG*) malloc(sizeof(TG));
        p->id_no = x;
        p->prox_no = g;
        p->prim_viz = NULL;
        g = p;
    }
    return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2){
    TG *p = TG_busca_no(g, no1);
    TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
    nova->id_viz = no2;
    nova->prox_viz = p->prim_viz;
    p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2){
    TVIZ *v = TG_busca_aresta(g, no1, no2);
    if(v) return;
    TG_ins_um_sentido(g, no1, no2);
    TG_ins_um_sentido(g, no2, no1);
}

void TG_retira_um_sentido(TG *g, int no1, int no2){
    TG *p = TG_busca_no(g, no1);
    if(!p) return;
    TVIZ *ant = NULL, *atual = p->prim_viz;
    while((atual)&&(atual->id_viz != no2)){
        ant = atual;
        atual = atual->prox_viz;
    }
    if(!ant) p->prim_viz = atual->prox_viz;
    else ant->prox_viz = atual->prox_viz;
    free(atual);
}

void TG_retira_aresta(TG *g ,int no1, int no2){
    TVIZ* v = TG_busca_aresta(g,no1,no2);
    if(!v) return;
    TG_retira_um_sentido(g,no1,no2);
    TG_retira_um_sentido(g,no2,no1);
}

TG* TG_retira_no(TG *g, int no) {
    TG *p = g, *ant = NULL;
    while ((p) && (p->id_no != no)) {
        ant = p;
        p = p->prox_no;
    }
    if (!p) return g;
    while (p->prim_viz) TG_retira_aresta(g, no, p->prim_viz->id_viz);
    if (!ant) g = g->prox_no;
    else ant->prox_no = p->prox_no;
    free(p);
    return g;
}
TVIZ* append(TVIZ* l, int x){
    TVIZ* new = malloc(sizeof(TVIZ));
    new->prox_viz = NULL;
    new->id_viz = x;
    if(!l)return new;
    TVIZ* p = l;
    while(p->prox_viz){
        p = p->prox_viz;
    }
    p->prox_viz = new;
    return l;
}
int tamCam(TVIZ* path){
    if(!path)return 0;
    int tam = 0;
    TVIZ* p = path;
    while(p){
        p = p->prox_viz;
        tam++;
    }
    return tam;
}

int maior_e(TG*g){
    int n = 0;
    TG* p = g;
    for(;p!= NULL;p = p->prox_no){
        if (p->id_no>n)n = p->id_no;
    }
    return n;
}

void teste(TG* g, int k_atual, int k,int dest, int atual, int caminho_atual,int* caminho,int* visitados){
    visitados[atual] = 1;   //para ter o caminho precisaria de +2 parametros, o menor caminho e o caminho atual
    caminho_atual++;    //caminho_atual += TG_busca_no(g,atual)->peso; caso o grafo seja com pesos.
                            //path = TLSE_insere(path, atual);
    k_atual++;
    if(k_atual> k)caminho_atual = INT_MAX;
    if(atual == dest){
        if (caminho_atual < *caminho)*caminho = caminho_atual;
    }
    else{
        TG* a = TG_busca_no(g,atual);
        TVIZ* viz = a->prim_viz;
        while(viz){
            if(!visitados[viz->id_viz]){
                teste(g, k_atual,k,dest,viz->id_viz,caminho_atual,caminho,visitados);
            }
            viz = viz->prox_viz;
        }
    }
    visitados[atual] = 0;
                            //TLSE* temp = path;
                            //path = path->prox;
                            //free(temp);
}

int caminho(TG*g, int inicio, int dest,int k){
    if(!g)return 0;
    int* visitados = calloc(maior_e(g)+1,sizeof(int));
    int *caminho_final = calloc(1,sizeof(int));
    *caminho_final = INT_MAX;
    teste(g,0,k,dest,inicio,0,caminho_final,visitados);
    int resultado = *caminho_final;
    free(caminho_final);
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
    TG_imprime(g);
  }while(1);
  
  int m;
  do{
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m);
    TG_imprime(g);
  }while(1);
  
  char op;
  printf("Digite n ou a para retirar nos ou arestas...\n");
  do{
    scanf(" %c", &op);
    if(op == 'n'){
      scanf("%d", &n);
      g = TG_retira_no(g, n);
      TG_imprime(g);
    }
    else if(op == 'a'){
      scanf("%d%d", &n, &m);
      TG_retira_aresta(g, n, m);
      TG_imprime(g);
    }
    else break;
  }while(1);
  int menor_cam = caminho(g,1,5,4);
  printf("MENOR CAM %d",menor_cam);
  TG_libera(g);
  return 0;
}

