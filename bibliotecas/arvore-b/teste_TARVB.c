#include "TARVB.h"
#include "../../TLSE.h"
#include "../TLSEINT.h"







TLSE* aux_retira_pares(TARVB* a, TLSE* l){
    if(!a)return l;
    int i;
    for(i = 0;i<a->nchaves;i++){
        l = aux_retira_pares(a->filho[i],l);
        if(a->chave[i]%2 == 0)l = TLSE_insere(l, a->chave[i]);
    }
    l = aux_retira_pares(a->filho[i],l);
    return l;
}


TARVB* retira_pares(TARVB* a,int t){
    if(!a)return NULL;
    TLSE* aux = NULL;
    aux = aux_retira_pares(a,aux);
    while(aux){
        a = TARVB_Retira(a,aux->info,t);
        aux = aux->prox;
    }
    return a;
}



int aux(TARVB*a, int elem){
    int i;
    for(i = 0;i<a->nchaves && a->chave[i]<elem;i++);
    TARVB* aux1 = a->filho[i];
    int j;
    for(j = 0;j<aux1->nchaves && aux1->chave[j]<=elem;j++){
        if(aux1->chave[j] == elem){
            if(a->chave[i])return a->chave[i];
            else return INT_MAX;
        }
    }
    return aux(aux1,elem);
}
TARVB* pai(TARVB*a, int elem){
    if(!a) return a;
    int i;
    for(i = 0; i < a->nchaves && a->chave[i] < elem; i++);
    int j;
    for(j = 0;j < a->filho[i]->nchaves && a->filho[i]->chave[j]<elem;j++);
    if(a->filho[i]->chave[j] == elem) return a;
    return pai(a->filho[i],elem);
}

int suc(TARVB* a,int elem){
    if(!a)return 0;
    TARVB* aux1 = TARVB_Busca(a, elem);
    if(!aux1)return a->chave[0];
    int i;
    for(i = 0;i<aux1->nchaves;i++){
        if(aux1->chave[i] == elem)break;
    }
    if (i < aux1->nchaves-1)return aux1->chave[i+1];

    return aux(a, elem);
}

TLSEINT* aux_misc(TARVB*a, int elem, TLSEINT* l){ //lim inf = maior num < elem lim sup = menor num > elem
    if(!a)return l;
    int i;
    for(i = 0;i <a->nchaves && a->chave[i] < elem;i++);
    int menor = elem;
    int maior = elem;
    int j;
    for(j = a->nchaves-1; j >= 0; j--){
        if(a->chave[j]<menor){
            menor = a->chave[j];
            break;
        }
    }
    for(j = 0;j<a->nchaves;j++) {
        if(a->chave[j]>maior){
            maior = a->chave[j];
            break;
        }
    }
    if(menor == elem)menor = INT_MIN;
    if(maior == elem)maior = INT_MAX;
    if(a->chave[i] == elem){
        l = TLSEINT_insere(l, menor, maior);
        return l;
    }
    l = aux_misc(a->filho[i],elem,l);
    l = TLSEINT_insere(l,menor,maior);
    return l;
}


void aux_mult(TARVB*a, int N, int M, int* ind,int* vet) {
    if(!a)return;
    int i;
    for(i = 0;i<a->nchaves;i++) {
        aux_mult(a->filho[i],N,M,ind,vet);
        if(a->chave[i] % N == 0 && a->chave[i] % M == 0){
            vet[*ind] = a->chave[i];
            (*ind)++;
        }
    }
    aux_mult(a->filho[i],N,M,ind,vet);
}

int contt(TARVB* a, int N, int M){
    if(!a)return 0;
    int i;
    int cont = 0;
    for(i = 0;i<a->nchaves;i++){
        cont +=contt(a->filho[i],N,M);
        if(a->chave[i] % N == 0 && a->chave[i] % M == 0)cont++;
    }
    cont +=contt(a->filho[i],N,M);
    return cont;
}



int* mult_NM(TARVB *a, int N, int M, int *tam_vet) {
    if (!a) {
        *tam_vet = 0;
        return NULL;
    }
    int tam;
    tam = contt(a, N, M);
    *tam_vet = tam;
    if(tam == 0)return NULL;
    int *vet = malloc(sizeof(int) * tam);
    int ind = 0;
    aux_mult(a,N,M,&ind,vet);
    return vet;
}








TLSEINT* misc(TARVB *a, int elem){
    if(!a)return NULL;
    TLSEINT* res = NULL;
    res = aux_misc(a,elem,res);
    return res;
}

TLSE* TLSE_append(TLSE* l1, TLSE* l2){
    if(!l1)return l2;
    TLSE* p = l1;
    while(p->prox){
        p = p->prox;
    }
    p->prox = l2;
    return l1;
}


TLSE* aux_maior(TARVB* a, TLSE* l, int N){
    if(!a)return l;
    int i;
    for(i = a->nchaves-1; i>=0;i--){
        if(a->chave[i]>N){
            l = aux_maior(a->filho[i+1],l,N);
            l = TLSE_insere(l, a->chave[i]);
        }
        else{
            break;
        }
    }
    l = aux_maior(a->filho[i+1],l,N);
    return l;
}

TLSE* aux_menor(TARVB* a, int N, TLSE* l){
    if(!a) return l;
    int i;
    for(i = 0;i<a->nchaves;i++){
        if(a->chave[i]<N){
            l = aux_menor(a->filho[i],N,l);
            l = TLSE_insere(l,a->chave[i]);
        }
        else break;
    }
    l = aux_menor(a->filho[i],N,l);
    return l;
}

TLSE* aux_entre(TARVB* a, int M, int N, TLSE* l){
    if(!a)return l;
    int i;

    for(i = 0;i<a->nchaves;i++){
        if(a->chave[i]>N && a->chave[i] < M){
            l = aux_entre(a->filho[i], M, N, l);
            l = TLSE_insere(l,a->chave[i]);
        }
    }
    l = aux_entre(a->filho[i],M,N,l);
    return l;
}

TLSE* entre_mN(TARVB* a, int M, int N){
    TLSE* res = NULL;
    if(N> M){
        int temp = M;
        M = N;
        N = temp;
    }
    res = aux_entre(a,M,N,res);
    return res;
}

TLSE* mN_maior(TARVB*a, int N){
    TLSE* res = NULL;
    res = aux_maior(a, res, N);
    return res;
}

TLSE* mN_menor(TARVB*a, int N){
    TLSE* res = NULL;
    res = aux_menor(a, N, res);
    return res;
}

int nivel_no(TARVB* a, TARVB* no){
    if(!a)return 0;
    if(a == no)return 1;
    TARVB* aux = TARVB_Busca(a,no->chave[0]);
    if(aux){
        int i;
        for(i = 0;i<a->nchaves && a->chave[i]<no->chave[0];i++);
        return nivel_no(a->filho[i],no)+1;
    }
    printf("a\n");
    return -1;
}



int main(int argc, char *argv[]){
    TARVB *arvore = TARVB_Inicializa();
    int t;
    printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
    scanf("%d", &t);
    if(t < 2) t = 2;
    int num = 0, from, to;
    while(num != -1){
        printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
        scanf("%d", &num);
        if(num == -9){
            scanf("%d", &from);
            arvore = TARVB_Retira(arvore, from, t);
            TARVB_Imprime2(arvore);
        }
        else if(num == -1){
            printf("\n");
            //TARVB_Imprime2(arvore);
            break;
        }
        else if(!num){
            printf("\n");
            TARVB_Imprime2(arvore);
        }
        else {
            arvore = TARVB_Insere(arvore, num, t);
            TARVB_Imprime2(arvore);
        }
        printf("\n\n");
    }
    /*int tam;
    int* vet = mult_NM(arvore,2,3,&tam);
    int i;
    for(i = 0;i<tam;i++){
        printf("%d ",vet[i]);
    }
    free(vet);*/
    /*TLSEINT* teste = misc(arvore, 42);
    TLSEINT_imprime(teste);
    TLSEINT_libera(teste);*/
    //printf("%d\n", suc(arvore,15));
    arvore = retira_pares(arvore,t);
    TARVB_Imprime2(arvore);
    TARVB_Libera(arvore);
    return 0;
}
