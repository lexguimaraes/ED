#include <string.h>
#include "TAB.h"

TAB *maior_elem(TAB *a){
  if(!a) return a;
  TAB *esq = maior_elem(a->esq), *dir = maior_elem(a->dir), *resp = a;
  if((esq) && (resp->info < esq->info)) resp = esq;
  if((dir) && (resp->info < dir->info)) resp = dir;
  return resp;
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
    printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posição E(ESQ) ou D(DIR)... ");
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

  resp = maior_elem(a);
  if(resp) printf("MAIOR ELEMENTO = %d\n", resp->info);
    
  TAB_libera(a);
  return 0;
}
