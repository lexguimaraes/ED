#include "TH.h"

typedef struct par{
  int num1, num2;
}TPAR;








void misc(char *arqa, char *arqb, char *saida, int k){
  FILE* t = fopen("dados1.bin","wb");
  if (!t)exit(1);
  fclose(t);
  TH_inicializa("tab1.bin","dados1.bin",k);
  TH_inicializa("tab2.bin","dados2.bin",k);
  FILE* a= fopen(arqa,"rb");
  int buff;
  while (fread(&buff,sizeof(int),1,a)) {
    TH_insere("tab1.bin","dados1.bin",k,buff);
  }
  fclose(a);
  a = fopen(arqb,"rb");
  while (fread(&buff,sizeof(int),1,a)) {
    TH_insere("tab2.bin","dados2.bin",k,buff);
  }
  fclose(a);
  FILE* hash = fopen("tab1.bin","rb");if (!hash)exit(1);
  int vet_a[k];
  fread(vet_a,sizeof(int),k,hash);
  fclose(hash);
  hash = fopen("tab2.bin","rb");if (!hash)exit(1);
  int vet_b[k];
  fread(vet_b,sizeof(int),k,hash);
  fclose(hash);int pos;int pos_b;
  FILE* da = fopen("dados1.bin","rb");
  FILE* db = fopen("dados2.bin","rb");
  for (int i = 1;i<k;i++) {
    pos = vet_a[i];
    while (pos!= -1) {
      fseek(da,pos,SEEK_SET);
      TA aux_a;
      fread(&aux_a,sizeof(TA),1,da);
      pos_b = vet_b[k-i];
      while (pos_b!= -1) {
        fseek(db,pos_b,SEEK_SET);
        TA aux_b;
        fread(&aux_b,sizeof(TA),1,db);
        FILE* fs = fopen(saida,"at");
        if (!fs)exit(1);
        fprintf(fs,"%d\n",aux_a.mat);
        fprintf(fs,"%d\n",aux_b.mat);
        fclose(fs);
        pos_b = aux_b.prox;
      }
      pos = aux_a.prox;
    }

  }
  fclose(da);
  fclose(db);
}

int main(void){
  int ant, num;
  char nome_dados1[31];
  printf("Digite o nome do primeiro arquivo de dados... ");
  scanf("%s", nome_dados1);


  //ARQS. BINÁRIOS
  FILE *fp = fopen(nome_dados1, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fwrite(&ant, sizeof(int), 1, fp);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fwrite(&num, sizeof(int), 1, fp);
    ant = num;
  }while(1);
  fclose(fp);

  char nome_dados2[31];
  printf("Digite o nome do segundo arquivo de dados... ");
  scanf("%s", nome_dados2);
  fp = fopen(nome_dados2, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fwrite(&ant, sizeof(int), 1, fp);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fwrite(&num, sizeof(int), 1, fp);
    ant = num;
  }while(1);
  fclose(fp);

  /*
  //ARQS. TEXTO
  FILE *fp = fopen(nome_dados1, "w");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fprintf(fp, "%d\n", ant);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
      fprintf(fp, "%d\n", num);
    ant = num;
  }while(1);
  fclose(fp);

  char nome_dados2[31];
  printf("Digite o nome do segundo arquivo de dados... ");
  scanf("%s", nome_dados2);
  fp = fopen(nome_dados2, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fprintf(fp, "%d\n", ant);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fprintf(fp, "%d\n", num);
    ant = num;
  }while(1);
  fclose(fp);
*/
  int k;
  printf("Digite o valor de k... ");
  scanf("%d", &k);

  char nome_saida[31];
  printf("Digite o nome do arquivo de dados de saida... ");
  scanf(" %s", nome_saida);
  misc(nome_dados1, nome_dados2, nome_saida, k);

  /*
  //ARQ. BINÁRIO
  fp = fopen(nome_saida, "rb");
  if(!fp) exit(1);
  int r;
  do{
    TPAR p;
    r = fread(&p, sizeof(TPAR), 1, fp);
    if(r != 1) break;
    printf("(%d,%d)\n", p.num1, p.num2);
  }while(1);
  fclose(fp);
  */

  //ARQ. TEXTO
  fp = fopen(nome_saida, "r");
  if(!fp) exit(1);
  int r;
  do{
    TPAR p;
    r = fscanf(fp,"%d%d", &p.num1, &p.num2);
    if(r != 2) break;
    printf("(%d,%d)\n", p.num1, p.num2);
  }while(1);
  fclose(fp);

  return 0;
}

