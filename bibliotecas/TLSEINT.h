#include <stdio.h>
#include <stdlib.h>

typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;

TLSEINT* TLSEINT_inicializa(void);
TLSEINT* TLSEINT_insere(TLSEINT *l, int inf, int sup);
void TLSEINT_imprime(TLSEINT *l);
void TLSEINT_libera(TLSEINT *l);
