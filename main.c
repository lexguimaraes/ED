#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct arvbin{
    int info;
    struct arvbin *esq, *dir;

}TAB;


TAB* TAB_cria(int v,TAB*esq, TAB*dir){
    TAB* new = malloc(sizeof(TAB));
    new->esq = esq;
    new->dir = dir;
    new->info = v;
    return new;
}

TAB* TAB_insere(int v, TAB* a){
    if(!a)return TAB_cria(v,NULL, NULL);
    if(a->info > v)a->esq = TAB_insere(v, a->esq);
    else if(a->info < v)a->dir = TAB_insere(v, a->dir);
    return a;
}
TAB* TABB_busca(int v, TAB* a){
    if(!a || a->info == v)return a;
    if(a->info < v)return TABB_busca(v,a->dir);
    return TABB_busca(v,a->esq);
}
TAB* TABB_retira(int v, TAB*a){
    if(!a)return a;
    if(v < a->info){
        a->esq = TABB_retira(v,a->esq);
    }
    else if(v > a->info){
        a->dir = TABB_retira(v,a->dir);
    }
    else{
        if(!a->esq && !a->dir){
            free(a);
            a = NULL;
        }
        else if(!a->esq || !a->dir){
            TAB* temp = a;
            if(a->esq)a = a->esq;
            else a = a->dir;
            free(temp);
        }
        else{
            TAB* temp = a->esq;
            while(temp->dir)temp = temp->dir;
            a->info = temp->info;
            temp->info = v;
            a->esq = TABB_retira(v, a->esq);
        }
    }
    return a;
}
void TAB_libera(TAB *a){
    if(a){
        TAB_libera(a->esq);
        TAB_libera(a->dir);
        free(a);
    }
}

void imp_aux(TAB *a, int andar){
    int j;
    if(a){
        imp_aux(a->dir, andar + 1);
        for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
        printf("%d\n", a->info);
        imp_aux(a->esq, andar + 1);
    }
    else{
        for(j = 0; j <= andar; j++) printf("\t");
        printf("N\n");
    }
}

void TAB_imp_ident(TAB *a){
    imp_aux(a, 0);
}


TAB* maior_abb(TAB *a) {
    if (!a)return a;
    TAB *dir = maior_abb(a->dir);
    TAB *m = a;
    if (dir)
        m = dir;
    return m;
}

TAB* menor_abb(TAB *a){
    if(!a)return a;
    TAB* esq = menor_abb(a->esq);
    TAB* m = a;
    if(esq){
        m = esq;
    }
    return m;
}
TAB* maior(TAB *a){
    if (!a)return a;
    TAB*esq = maior(a->esq);
    TAB*dir = maior(a->dir);
    TAB* m = a;
    if(esq && esq->info > m->info){
        m = esq;
    }
    if(dir && dir->info > m->info){
        m = dir;
    }
    return m;
}
TAB* TAB_busca(TAB* a, int v) {
    if(!a)return a;
    if(a->info == v)return a;
    TAB* tes = TAB_busca(a->esq,v);
    if(tes)return tes;
    return TAB_busca(a->dir,v);

}

TAB* TABB_retira_impar(TAB* a){
    if(!a)return a;
    a->esq = TABB_retira_impar(a->esq);
    a->dir = TABB_retira_impar(a->dir);
    if(a->info % 2 != 0){
        return TABB_retira(a->info,a);
    }
    return a;
}
int numnos(TAB* a){
    if(!a)return 0;
    return numnos(a->esq)+numnos(a->dir)+1;
}

void p_vet(TAB* a,int *vet,int *pos,int N){
    if(!a || !vet)return;
    p_vet(a->esq,vet,pos,N);
    p_vet(a->dir,vet,pos,N);
    if(a->info < N){
        (*pos)++;
        vet[*pos] = a->info;
    }
    printf("%d ",vet[*pos]);
}


int* mN(TAB*a, int N){
    if(!a)return NULL;
    if(a->info >= N){
        return mN(a->esq, N);
    }
    int n_nos = numnos(a);
    int* resp = malloc((n_nos+1)*(sizeof(int)));
    int pos = 0;
    p_vet(a,resp,&pos,N);
    return resp;
}

int aux(TAB* arv, TAB* tmp, int S){
    if(!arv || !tmp)return 0;
    if(arv->info < S){
        if(TABB_busca(S - arv->info,tmp))return 1;
    }
    if (aux(arv->esq,tmp,S)== 1) return 1;
    return aux(arv->dir,tmp,S);
}



int temPar(TAB* arv, int S){
    return aux(arv, arv, S);
}

int main(void) {
    TAB *a = NULL;
    int n;

    while(1){
        scanf("%d", &n);
        if(n < 0) break;
        a = TAB_insere(n, a);
    }
    //TAB_imp_ident(a);
    //a = TABB_retira_impar(a);
    TAB_imp_ident(a);
    printf("%d", temPar(a, 15));
    //int*vet = mN(a,15);

    TAB_libera(a);
    return 0;
}

