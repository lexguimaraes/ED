#include <limits.h>
#include "TARVB.h"
#include "TLSE.h"


//Questão original

/*TLSE* cont(TARVB* a ,int ind, TLSE* l) { // FUNCAO EXATAMENTE IGUAL NA CORREÇÃO
  if (!a)return l;
  for (int i = 0;i<= a->nchaves;i++) {
    l = cont(a->filho[i],ind, l);
    if (i == ind && i<a->nchaves) l = TLSE_insere(l,a->chave[i]);
  }
  return l;
}


int* todos_ind(TARVB *a, int ind, int *tam_vet){
  TLSE* res = cont(a,ind,NULL);
  while (res){         //ERREI AQUI
    (*tam_vet)++;
    res = res->prox;
  }
  int temp = *tam_vet;
  int* vet = malloc(sizeof(int)*temp);
  temp = 0;
  while (res) {    //ERREI AQUI, ALÉM DE NÃO LIBERAR A LISTA
    vet[temp] = res->info;
    res = res->prox;
    temp++;
  }
  return vet;
}
*/

//CORREÇÃO

TLSE* cont(TARVB* a ,int ind, TLSE* l) { // FUNCAO EXATAMENTE IGUAL A DA PROVA
  if (!a)return l;
  for (int i = 0;i<= a->nchaves;i++) {
    l = cont(a->filho[i],ind, l);
    if (i == ind && i < a->nchaves) l = TLSE_insere(l,a->chave[i]);
  }
  return l;
}

int* todos_ind(TARVB *a, int ind, int *tam_vet) {
  TLSE* res = cont(a,ind,NULL); //IGUAL A PROVA
  (*tam_vet) = 0; // ESQUECI ISSO NA PROVA
  TLSE* tmp = res; // USAR TMP, ESQUECI NA PROVA TAMBEM
  while (tmp){         //AJUSTANDO PARA TMP
    (*tam_vet)++;
    tmp = tmp->prox;
  }
  int temp = *tam_vet; // IGUAL A PROVA
  int* vet = malloc(sizeof(int)*temp); //IGUAL A PROVA
  temp--; //AO INVES DE COMEÇAR DO 0, COMEÇANDO DO ULTIMO INDICE PARA SER CRESCENTEEEEEEEE
  tmp = res; // FALTOU NA PROVA...
  while (tmp) {    //USANDO TMP AQUI
    vet[temp] = tmp->info; // IGUAL A PROVA
    tmp = tmp->prox;  // IGUAL A PROVA
    temp--; // COMEÇANDO DO FINAL E SUBTRAINDO
  }
  TLSE_libera(res); // ESQUECI NA PROVA TAMBÉM
  return vet; // IGUAL A PROVA
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
