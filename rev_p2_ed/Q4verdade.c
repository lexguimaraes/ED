#include <stdio.h>
#include <stdlib.h>

int esq (int ind){
    return 2 * ind + sizeof(int);
}


int dir (int ind){
    return 2 * (ind + sizeof(int));
}


int pai(int ind){
    if(ind) return (((ind - sizeof(int))/sizeof(int))/2) * sizeof(int);
    return -1;
}


int tam(char* narq) {
    int tam = 0;int buff;
    FILE* f = fopen(narq, "rb");
    if (!f)return 0;
    while (fread(&buff, sizeof(int), 1, f)) {
        tam+=sizeof(int);
    }
    fclose(f);
    return tam;
}


void min_heapfy(char* narq, int ind) {
    int e = esq(ind);
    int d = dir(ind);
    int menor = ind;
    int te, td, tm;
    int n = tam(narq);
    FILE* f = fopen(narq, "rb+");
    if (!f)exit(1); // TROQUEI RETURN POR EXIT
    fseek(f,e ,SEEK_SET);
    fread(&te, sizeof(int),1,f);
    fseek(f,menor,SEEK_SET);
    fread(&tm,sizeof(int),1,f);
    if (e<n && te<tm)menor = e;
    fseek(f,menor,SEEK_SET);
    fread(&tm,sizeof(int),1,f);
    fseek(f,d,SEEK_SET);
    fread(&td,sizeof(int),1,f);
    if (d<n && td<tm)menor = d;
    if (menor!= ind) {
        fseek(f,menor,SEEK_SET);
        int temp;int tend = menor;int tind;
        fread(&temp,sizeof(int),1,f);
        fseek(f,ind,SEEK_SET);
        fread(&tind, sizeof(int),1,f);
        fseek(f,ind,SEEK_SET);
        fwrite(&temp,sizeof(int),1,f);
        fseek(f,menor,SEEK_SET);
        fwrite(&tind,sizeof(int),1,f);
        fclose(f);
        return min_heapfy(narq,menor);
    }
    fclose(f);
}
int main(void){
    char nome_arq[31];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arq);
    int nvet, i = 1, aux;
    printf("Digite o numero de elementos distintos do arquivo: ");
    scanf("%d", &nvet);
    if(nvet <= 0) return 0;
    int vet[nvet];
    scanf("%d", &vet[0]);
    while (i < nvet){
        scanf("%d", &aux);
        if(aux > vet[i - 1]) vet[i++] = aux;
    }

    vet[0] = vet[i - 1] + 1;
    FILE *fp = fopen(nome_arq, "wb");
    if(!fp) exit(1);
    fwrite(&vet, sizeof(int), nvet, fp);
    fclose(fp);

    min_heapfy(nome_arq, 0);

    int resp[nvet];
    fp = fopen(nome_arq, "rb");
    if(!fp) exit(1);
    fread(&resp, sizeof(int), nvet, fp);
    fclose(fp);

    printf("\nVerificacao da operacao min_heapfy...\n");
    for(i = 0; i < nvet; i++) printf("[%d]:\t%d\t%d\n", i, vet[i], resp[i]);

    return 0;
}

