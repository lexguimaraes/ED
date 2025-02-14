#include <limits.h>
#include "TARVB.h"
#include "TLSE.h"




TLSE* cont(TARVB* a ,int ind, TLSE* l) {
  if (!a)return l;
  for (int i = 0;i<= a->nchaves;i++) {
    l = cont(a->filho[i],ind, l);
    if (i == ind && i < a->nchaves) l = TLSE_insere(l,a->chave[i]);
  }
  return l;
}

int* todos_ind(TARVB *a, int ind, int *tam_vet) {
  TLSE* res = cont(a,ind,NULL);
  (*tam_vet) = 0;
  TLSE* tmp = res;
  while (tmp){
    (*tam_vet)++;
    tmp = tmp->prox;
  }
  int temp = *tam_vet;
  int* vet = malloc(sizeof(int)*temp);
  temp--;
  tmp = res;
  while (tmp) {
    vet[temp] = tmp->info;
    tmp = tmp->prox;
    temp--;
  }
  TLSE_libera(res);
  return vet;
}





int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num;
  do{
    scanf("%d", &num);
    if(num <= 0) break;
    arvore = TARVB_Insere(arvore, num, t);
    TARVB_Imprime(arvore);
  }while(1);


  if(arvore){
    int ind, tam_vet = 0;
    scanf("%d", &ind);
    printf("%d\n", ind);
    int *resp = todos_ind(arvore, ind, &tam_vet);
    if(tam_vet){
      int i;
      for(i = 0; i < tam_vet; i++) printf("resp[%d] = %d\n", i, resp[i]);
      free(resp);
    }
  }

  TARVB_Libera(arvore);
  return 0;
}
