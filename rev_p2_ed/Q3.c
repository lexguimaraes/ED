#include "TH.h"

typedef struct par{
  int num1, num2;
}TPAR;
// NAO PUS ORIGINAL PORQUE,
// FORA OS COMENTÁRIOS TÁ RODANDO EXATAMENTE IGUAL A PROVA, ABSOLUTAMENTE UNICAS DIFERENÇAS SÃO MODE "rb", QUE TINHA ESQUECIDO EM 4 fopens, COMENTEI QUAIS ERAM
// ONDE NAO TEM COMETÁRIO ESTÁ IGUAL, RODOU AQUI EM UBUNTU 24.01LTS
void misc(char *arqa, char *arqb, char *saida, int k){
  FILE* t = fopen("dados1.bin","wb");
  if (!t)return;
  fclose(t);
  TH_inicializa("tab1.bin","dados1.bin",5);
  TH_inicializa("tab2.bin","dados2.bin",5);
  FILE* a= fopen(arqa,"rb");
  int buff;
  while (fread(&buff,sizeof(int),1,a)) {
    TH_insere("tab1.bin","dados1.bin",5,buff);
  }
  fclose(a);
  a = fopen(arqb,"rb");
  while (fread(&buff,sizeof(int),1,a)) {
    TH_insere("tab2.bin","dados2.bin",5,buff);
  }
  fclose(a);
  FILE* hash = fopen("tab1.bin","rb");if (!hash)return;// NAO TINHA POSTO O MODO DE ABERTURA;
  int vet_a[5];
  fread(vet_a,sizeof(int),5,hash);
  fclose(hash);
  hash = fopen("tab2.bin","rb");if (!hash)return; //MESMA COISA, NAO TINHA POSTO O MODO
  int vet_b[5];
  fread(vet_b,sizeof(int),5,hash);
  fclose(hash);int pos;int pos_b;
  FILE* da = fopen("dados1.bin","rb"); // MESMA COISA AAAAAAAAAA
  FILE* db = fopen("dados2.bin","rb"); // ...
  for (int i = 0;i<5;i++) {
    pos = vet_a[i];
    while (pos!= -1) {
      fseek(da,pos,SEEK_SET);
      TA aux_a; // USANDO TA PORQUE A BIBLIOTECA TA DIFERENTE, MAS NA PROVA FOI TNUM
      fread(&aux_a,sizeof(TA),1,da);
      for (int j = 0;j<5;j++) {
        pos_b = vet_b[j];
        while (pos_b!= -1) {
          fseek(db,pos_b,SEEK_SET);
          TA aux_b;
          fread(&aux_b,sizeof(TA),1,db);
          if (((aux_a.mat % k) + (aux_b.mat % k)) == k) {
            FILE* fs = fopen(saida,"at");
            if (!fs)return;
            fprintf(fs,"%d\n",aux_a.mat);
            fprintf(fs,"%d\n",aux_b.mat);
            fclose(fs);
          }
          pos_b = aux_b.prox;
        }

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
