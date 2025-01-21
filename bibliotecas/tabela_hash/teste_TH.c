#include "TH.h"
#include "../../TLSE.h"
#include "string.h"


void inter(char* arq1, char* arq2, char* saida) {
    int buffer;
    FILE *f = fopen(arq1, "rt");
    if (!f)return;
    TH_inicializa("Hash.bin", 5);
    while (fscanf(f, "%d", &buffer) == 1) {
        TH_insere("Hash.bin", "Dados.bin", 5, buffer);
    }
    fclose(f);
    f = fopen(arq2, "rt");
    if (!f)return;
    while (fscanf(f, "%d", &buffer) == 1) {
        TH_insere("Hash.bin", "Dados.bin", 5, buffer);
    }
    fclose(f);
    int pos;
    int i;
    FILE *dados = fopen("Dados.bin", "rb");
    FILE *Hash = fopen("Hash.bin", "rb");
    for (i = 0; i < 5; i++) {
        fread(&pos, sizeof(int), 1, Hash);
        while (pos != -1) {
            fseek(dados, pos, SEEK_SET);
            TNUM aux;
            fread(&aux, sizeof(TNUM), 1, dados);
            if (aux.qtde == 2) {
                FILE *fs = fopen(saida, "at");
                if (!fs)return;
                fprintf(fs, "%d\n", aux.num);
                fclose(fs);
            }
            pos = aux.prox;
        }
    }
    fclose(dados);
    fclose(Hash);
}


void uniao(char* arq1, char* arq2, char* saida){
    FILE* t = fopen("Dados.bin","wb");
    if(!t)return;
    fclose(t);
    TH_inicializa("tabela.bin",5);
    FILE* f = fopen(arq1,"rt");
    if(!f)return;
    int buffer;
    while(fscanf(f,"%d",&buffer) == 1){
        TH_insere("tabela.bin","Dados.bin",5,buffer);
    }
    f = fopen(arq2,"rt");
    if(!f)return;
    while(fscanf(f,"%d",&buffer) == 1){
        TH_insere("tabela.bin","Dados.bin",5,buffer);
    }
    FILE* hash = fopen("tabela.bin","rb");
    int vet[5];
    fread(vet, sizeof(int),5,hash);
    fclose(hash);
    int pos;
    int j;
    FILE* dados = fopen("Dados.bin","rb");
    for(j=0;j<5;j++){
        pos = vet[j];
        while(pos!= -1){
            TNUM aux;
            fseek(dados,pos,SEEK_SET);
            fread(&aux,sizeof(TNUM),1,dados);
            FILE* fs = fopen(saida,"at");
            if(!fs)return;
            fprintf(fs,"%d\n",aux.num);
            fclose(fs);
            pos = aux.prox;
        }
    }
    fclose(dados);
}

void dif_sim(char* arq1, char* arq2, char* saida){
    TH_inicializa("tabela.bin",5);
    int buffer;
    FILE* f = fopen(arq1,"rt");
    if(!f)return;
    while(fscanf(f,"%d",&buffer)==1){
        TH_insere("tabela.bin","Dados.bin",5,buffer);
    }
    fclose(f);
    f = fopen(arq2,"rt");
    if(!f)return;
    while(fscanf(f,"%d",&buffer)==1){
        TH_insere("tabela.bin","Dados.bin",5,buffer);
    }
    fclose(f);
    FILE* hash = fopen("tabela.bin","rb");
    if(!hash)return;
    int vet[5];
    fread(&vet, sizeof(int),5,hash);
    fclose(hash);
    FILE* dados = fopen("Dados.bin","rb");
    if(!dados)return;
    int i;
    for(i = 0;i<5;i++){
        int pos = vet[i];
        while(pos!=-1){
            fseek(dados, pos,SEEK_SET);
            TNUM aux;
            fread(&aux, sizeof(TNUM),1,dados);
            if(aux.qtde == 1){
                FILE* fs = fopen(saida, "at");
                if(!fs)return;
                fprintf(fs,"%d\n",aux.num);
                fclose(fs);
            }
            pos = aux.prox;
        }
    }
    fclose(dados);
}














void misc(char **arqs, int num_arqs, char *saida){
    FILE* t = fopen("Dados.bin","wb");
    if(!t)return;
    fclose(t);
    int buffer;
    int i;
    TH_inicializa("tabela.bin",5);
    for(i = 0;i<num_arqs;i++) {
        FILE *f = fopen(arqs[i], "rt");
        while (fscanf(f, "%d", &buffer) == 1) {
            TH_insere("tabela.bin", "Dados.bin", 5, buffer);
        }
        fclose(f);
    }
    FILE* hash = fopen("tabela.bin","rb");
    int j;
    for(j = 0;j<5;j++){
        TNUM aux;
        int pos;
        fread(&pos,sizeof(int),1,hash);
        FILE* dados = fopen("Dados.bin","rb");
        while(pos!=-1){
            fseek(dados,pos,SEEK_SET);
            fread(&aux,sizeof(TNUM),1,dados);
            if(aux.qtde%2!=0){
                FILE* fs = fopen(saida, "at");
                fprintf(fs,"%d\n",aux.num);
                fclose(fs);
            }
            pos = aux.prox;
        }
        fclose(dados);
    }
    fclose(hash);
}



void misc2(char **arqs, int num_arqs,int porc, char *saida){
    int i;
    int buffer;
    int cont = 0;
    TH_inicializa("tabela.bin",5);
    for(i = 0;i<num_arqs;i++){
        FILE* f = fopen(arqs[i],"rt");
        while(fscanf(f,"%d",&buffer)==1){
            TH_insere("tabela.bin","dados.bin",5,buffer);
            cont++;
        }
    }
    int pos;
    FILE* hash = fopen("tabela.bin","rb");
    int j;
    double porce = 1.0*porc/100;
    for(j = 0;j<5;j++){
        fread(&pos,sizeof(int),1,hash);
        if(pos!=-1){
            TNUM aux;
            FILE* dados = fopen("dados.bin","rb");
            fseek(dados,pos,SEEK_SET);
            fread(&aux,sizeof(TNUM),1,dados);
            double temp = 1.0*aux.qtde/cont;

            if(temp >= porce){
                FILE* fs =fopen(saida,"at");
                fprintf(fs,"%d\n",aux.num);
                fclose(fs);
            }
            while(aux.prox!=-1){
                fseek(dados,aux.prox,SEEK_SET);
                fread(&aux, sizeof(TNUM),1,dados);
                temp = 1.0*aux.qtde/cont;
                if(temp == porce){
                    FILE* fs =fopen(saida,"at");
                    fprintf(fs,"%d\n",aux.num);
                    fclose(fs);
                }
            }
            fclose(dados);
        }
    }
    fclose(hash);
}




int main(void){
    FILE* fp = fopen("arquivo1.txt","wb");
    int i;
    for(i = 1;i<=100;i++){
        fprintf(fp,"%d\n",i);
    }
    fclose(fp);
    fp = fopen("arquivo2.txt","wb");
    for(i = 50;i<=150;i++){
        fprintf(fp,"%d\n",i);
    }
    fclose(fp);
    char** teste = malloc(sizeof(char*)*2);
    teste[0] = malloc(15);
    teste[1] = malloc(15);
    strcpy(teste[0],"arquivo1.txt");
    strcpy(teste[1],"arquivo2.txt");
    misc(teste, 2, "saida.txt");
    free(teste[0]);
    free(teste[1]);
    free(teste);
    return 0;
}