#include <stdio.h>


#define MAX 2000000000
int TAM_VET = 0;


void descer(int i, int n, int *T){
    int j = 2*i;

    if(i==0) j=1;

    if(j <= n){
        if(j < n){
            if(T[j+1] > T[j]){
                j=j+1;
            }
        }
        if(T[i] < T[j]){
            int t = T[i];
            T[i] = T[j];
            T[j] = t;

            descer(j, n, T);
        }
    }

}

void subir(int i, int *T){
    int p;

    if(i == 3 || i == 4)        p = 1; 
    else if(i == 1 || i == 2)   p = 0;
    else                        p = (i /2)-1;

    if(p>=0){
        if(T[i] > T[p]){
            int temp = T[i];
            T[i] = T[p];
            T[p] = temp;

            subir(p, T);
        }
    }
}

void inserir(int novo, int *T){
    if(TAM_VET <= MAX){
        T[TAM_VET] = novo;
        TAM_VET++;
        subir(TAM_VET-1, T);
    }
}

int remover(int *T){
    int aux; 
    if(TAM_VET > 0){
        aux = T[0];
        T[0] = T[TAM_VET-1];
        TAM_VET--;
        descer(0, TAM_VET-1, T);
    }

    return aux;
}

void construir(int *T, int n){
    int i;
    for(i=n/2; i >= 0; i--){
        descer(i, n, T);
    }
}

void heapsort(int *A, int n){
    construir(A, n-1);

    int i;

    for(i = n-1; i > 0;i--){

        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        descer(0, i-1, A);
    }

}