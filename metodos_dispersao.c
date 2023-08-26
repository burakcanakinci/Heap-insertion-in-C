#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 2000000000


int busca(int *v, int Tam, int valor){
    int *i = v;
    int *last = &v[Tam];
    
    for(; i <= last; i++){
        if(*i == valor)
            return 1;
    }

    return 0;
}

int metodo_div(int chave, int n){
    return chave % n;
}

int* add_zeros(int *chave, int dif, int chave_n){
        int *novo = malloc(sizeof(int) * (chave_n + dif));
        int i, cont=0;

        for(i = 0; i< (dif+chave_n); i++){
            if(i < dif){
                novo[i] = 0;
            }else{
                novo[i] = chave[cont];
                cont++;
            }
        }

        return novo;
}

int metodo_dobra(int *chave, int chave_n, int n){
    int aux = log10(n)/log10(10);

    if(chave_n < aux*2){


        int dif = aux*2 - chave_n;

        

        chave = add_zeros(chave, dif, chave_n);
        chave_n = chave_n + dif;

    }

    char str_aux[aux];
    int j, k, i;

    for(i=0; i < chave_n-aux; i=i+aux){
        for(j=(aux+i)-1, k = i+aux; j >= i;j--, k++){
            chave[k] = chave[j] + chave[k];

            if(chave[k] > 9){
                chave[k] = chave[k] % 10;
            }
        }
    }

    int cont=0;
    for(i=chave_n-aux; i < chave_n; i++){
        str_aux[cont] = chave[i] + '0';
        cont++;
    }

    str_aux[cont] = '\0';

    return atoi(str_aux);


}

int metodo_multiplicacao(int chave, int n){
    int aux = log10(n)/log10(10);

    char aux_str[aux];

    chave = chave*chave;

    int i = 0;
    for(i = aux-1; i >= 0; i--){
        aux_str[i] = chave%10 + '0';
        chave = chave/10;
    }

    aux_str[i] = '\0';
    return atoi(aux_str);
}

int duplic = 0;

int* gerarVetor(int Tam){
    int* v = malloc(Tam*sizeof(int));

    int i;

    srand((unsigned)time(NULL));

    for(i =0; i< Tam;){
        int value = rand() % __INT_MAX__;
            v[i] = value;
            i++;
    }

    return v;
}

float modulo(float x){
    if(x >= 0)
        return x;
    
    return -(x);
}
int num_Digits(int num){
    int valor = num;
    int numDigitos = 0;
    while(valor/10 != 0){
        valor = valor/10;
        numDigitos++;
    }

    return numDigitos;
}

int * int2Vector(int num, int *tam){
    int numDigitos = 1;
    int valor = num;

    while(valor/10 != 0){
        valor = valor/10;
        numDigitos++;
    }

    *tam = numDigitos;

    int *vector = malloc(sizeof(int)*numDigitos);

    int i;

    for(i = numDigitos-1; i >= 0; i--){
        vector[i] = num%10;
        num = num/10;
    }

    return vector;
}


double calcula_desvio_digito(int digit, int *chaves, int n, int tam_chave, int desvio_somatorio){
    int digits_soma[] = {0,0,0,0,0,0,0,0,0,0};
    double desvio=0;
    int i;
    for(i = 0; i<n;i++){
        int num_digits_t;
        int *num = int2Vector(chaves[i], &num_digits_t);

        if(num_digits_t < tam_chave){

            int dif = tam_chave - num_digits_t;

            num = add_zeros(num, dif, num_digits_t);
        
        }
        

        switch(num[digit]){
            case 0: digits_soma[0]++; break;
            case 1: digits_soma[1]++; break;
            case 2: digits_soma[2]++; break;
            case 3: digits_soma[3]++; break;
            case 4: digits_soma[4]++; break;
            case 5: digits_soma[5]++; break;
            case 6: digits_soma[6]++; break;
            case 7: digits_soma[7]++; break;
            case 8: digits_soma[8]++; break;
            case 9: digits_soma[9]++; break;
        }
    }

    for(i = 0; i<10;i++){
        double somatorio;

        somatorio = (double)(digits_soma[i] - (n/10.0));
        
        if(desvio_somatorio)
            desvio = desvio + (modulo(somatorio));
        else
            desvio = desvio + (pow(somatorio, 2));
    }


    return desvio;
}

int melhorDesvio(double *d, int tam){
    int melhor = 0;
    int i;
    for(i = 0; i < tam; i++){
        if(d[melhor] > d[i]){
            melhor = i;
        }
    }

    return melhor;
}
int metodo_analise_digitos(int *vet_chaves, int n, int* tabela, int n_t, int desvio){
    int aux = log10(n)/log10(10);
    int num_colisoes=0;
    double *desvios = malloc(sizeof(double) * 10);
    int melhores_desvios[aux];
    int cont = 0;
    int i;

    for(i = 0; i < 10; i++){
        desvios[i] = calcula_desvio_digito(i, vet_chaves, n, 10, desvio);
    }

    for(i = 0; i<aux;i++){
        int menor_desvio = melhorDesvio(desvios, 10);
        desvios[menor_desvio] = 2147483647;

        melhores_desvios[i] = menor_desvio;

    }


    
    for(i = 0; i<n; i++){
        int tam_chave;
        int *chave_vet = int2Vector(vet_chaves[i], &tam_chave);
        int j;
        char temp_chave[aux];
        
        for(j =0; j < aux; j++){
            int index = melhores_desvios[j];
            int digit = chave_vet[index];
            temp_chave[j] = digit + '0';
        }
        
        
        int aux_num = atoi(temp_chave);

        
        if(aux_num <= n_t && tabela[aux_num] == -1){
                tabela[aux_num] = vet_chaves[i];
        }else{
                num_colisoes++;
        }
        
    }
    
    return num_colisoes;

}

