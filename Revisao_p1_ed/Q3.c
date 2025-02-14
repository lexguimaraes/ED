#include <string.h>
#include "TABB.h"

//VER SER TABB É AVL

int altura_no(TABB* a){
    if(!a)return -1;
    int altura_esq = altura_no(a->esq);
    int altura_dir = altura_no(a->dir);
    if (altura_esq > altura_dir)return altura_esq+1;
    return altura_dir+1;
}
int fb(TABB* a){
    if(!a)return 0;
    return altura_no(a->esq) - altura_no(a->dir);
}

int abbeAVL(TABB*a){
    if(!a)return 1;
    if (abs(fb(a))>= 2)return 0;
    int tmp = abbeAVL(a->esq);
    if(!tmp)return 0;
    return abbeAVL(a->dir);
}

int main(void){
  int n, m;
  TABB *a = NULL;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(n, a);
    TABB_imprime(a);
  }
  TABB_imprime(a);
  
  printf("a e AVL? %d\n", abbeAVL(a));
  TABB_libera(a);
  return 0;
}
