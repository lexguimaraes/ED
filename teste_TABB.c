

int main(void){
  TABB *a = TABB_inicializa(); 
  int n;

  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(a, n);
  }
  TABB_imp_ident(a);

  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_retira(a, n);
    TABB_imp_ident(a);
  }
  
  TABB_libera(a);
  return 0;
} 
