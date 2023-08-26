#include <stdio.h>


void insertionsort(int *v, int Tam){
    int j, i;
    int chave;
    for(j = 1; j <= Tam; j++){
        chave = v[j];

        i = j-1;

        while(i >= 0 && v[i] > chave){
            v[i+1] = v[i];
            i = i -1;
        }

        v[i+1] = chave;

        
    }
}