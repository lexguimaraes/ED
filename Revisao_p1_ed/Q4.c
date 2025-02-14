#include <string.h>
#include "TAB.h"

//FOLHAS NO MESMO NIVEL, FILHOS DA DIREITA TEM QUE TER FILHOS NA DIREITA E VICE VERSA EM NOS DE NIVEL IMPAR, E NOS DE NIVEL PAR TEM QUE DOIS FILHOS

int nivel (TAB* a, TAB* aux){
    if (a==aux) return 0;
    if (TAB_busca(a->esq,aux->info)) {
        return nivel(a->esq,aux) + 1;
    }
    return nivel(a->dir,aux) + 1;
}

TAB* folha(TAB* a){
    if (!a->esq && !a->dir) {
        return a;
    }
    if (a->esq) {
        return folha(a->esq);
    }
    return folha(a->dir);
}

int checa_nos (TAB *a, TAB *aux, int dir){
    if (!a) return 1;
    int n = nivel(aux,a);
    if (n%2==0){
        if ((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
        return (checa_nos(a->esq,aux,0) && checa_nos(a->dir,aux,1));
    } else{
        if (dir==0){
            if (a->dir || !a->esq) return 0;
            return checa_nos(a->esq,aux,0);
        }
        else{
            if (a->esq || !a->dir) return 0;
            return checa_nos(a->dir,aux,1);
        }
    }
}

int checa_folhas (TAB *a, TAB *aux, int n){
    if (!aux->esq && !aux->dir){
        int b = nivel(a,aux);
        if (b==n && b%2==0) return 1;
        return 0;
    }
    if (aux->esq && aux->dir) {
        return ( ( checa_folhas(a,aux->esq,n) && checa_folhas(a,aux->dir,n) ) );
    }
    if (aux->esq) {
        return checa_folhas(a,aux->esq,n);
    }
    return checa_folhas(a,aux->dir,n);
}


int teste (TAB *a){
    if (!a) return 0;
    if((!a->esq && a->dir) || (a->esq && !a->dir)) return 0;
    if (!a->esq && !a->dir) return 1;
    TAB* aux = a;
    TAB* f = folha(a);
    int n = nivel(aux,f);
    return ((checa_nos(aux->esq,aux,0) && checa_nos(aux->dir,aux,1) && checa_folhas(aux,aux,n)));
}













int main(void){
  int no, pai;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAB *a = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a, pai);
    if(!resp){
      TAB_libera(a);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a);
  printf("\n");
  
  printf("Segue o padrao? %d\n", teste(a));
  TAB_libera(a);
  return 0;
}
