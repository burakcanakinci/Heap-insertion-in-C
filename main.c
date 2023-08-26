//Aluno: Francisco Micael de Araujo Lima    476489

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "heapsort.h"
#include "insertionsort.h"
#include "metodos_dispersao.h"
#define MAX 2000000000
#define CLOCKS_PER_SEC ((__clock_t) 1000000)

//exportando tamanho de vetor da parte
//de funcoes de heap.
extern int TAM_VET;

/* Funcao auxiliar
*  Copia um vetor de inteiro para outro
*/
void vetcpy(int *v1, int *v2, int TAM);

/* Funcao auxiliar
*  Verifica se um vetor é igual ao outro
*/
int equals(int *v1, int *v2, int TAM);

/* Funcao auxiliar
*  Calcula o tempo para cada um dos
*  algoritmos (heapsort e insertion sort)
*  considerando o tamanho n.
*/
void calcula_tempo_algoritmos(int tam);

/* Funcao auxiliar
*  Calcula o tempo de execucao para
*  um conjunto de chaves e um tamanho n.
*  Sao enviados os vetores com tamanho 100000
*  para cada metodo de dispersao.
*/
void calcula_colisoes_dispersao(int *div, int *dobra, int* mult, int* analise1, int* analise2, int *chaves, int n);


//Menu para realizar operacoes
int menu(int *v_heap);


int main(){
    int op;

    //vetor para testar heap
    int *v_heap = malloc(sizeof(int) * MAX);

    //Definicoes dos vetores para metodos de dispersao
    int *v1 = malloc(sizeof(int)*100000);
    int *v2 = malloc(sizeof(int)*100000);
    int *v3 = malloc(sizeof(int)*100000);
    int *v4 = malloc(sizeof(int)*100000);
    int *v5 = malloc(sizeof(int)*100000);

    //Menu
    for(;;){
        int op = menu(v_heap);

        if(op == 1){
            int valor;
            printf("Valor a inserir: ");
            scanf("%d", &valor);

            inserir(valor, v_heap);
        }else if(op == 2){
            printf("%d removido.\n", remover(v_heap));

        }else if(op == 3){
            heapsort(v_heap, TAM_VET);

        }else if(op == 4){
            insertionsort(v_heap, TAM_VET-1);

        }else if(op == 0){
            break;
        }
        
    }

    //Tempo dos algoritmos para n
    calcula_tempo_algoritmos(1000);
    calcula_tempo_algoritmos(50000);
    calcula_tempo_algoritmos(500000);
    calcula_tempo_algoritmos(1000000);

    //Calculando as colisoes em metodos de dispersao
    int n = 200000;

    for(n; n <= 1000000; n=n+200000){
        printf("\nColisoes para N = %d\n\n", n);

        //Gera chaves aleatorias entre 0 e 2B, tam = n
        int *chaves = gerarVetor(n);

        calcula_colisoes_dispersao(v1, v2, v3, v4, v5, chaves, n);   
    }
    
    return 0;
    
}
    

void vetcpy(int *v1, int *v2, int TAM){
    int i;
    for(i = 0; i<TAM; i++){
        v2[i] = v1[i];
    }
}

int equals(int *v1, int *v2, int TAM){
    int i;

    for(i = 0; i<TAM; i++){
       if(v2[i] != v1[i]){
           return 1;
       }
    }

    return 0;

}


void calcula_tempo_algoritmos(int tam){
    int *v1 = gerarVetor(tam);
    int *v1_copy = malloc(tam*sizeof(int));
    clock_t inicio, fim;

    vetcpy(v1, v1_copy, tam);


    printf("\n\nTime: Vector %d elements.\n\n", tam);
    
    
    inicio= clock();

    insertionsort(v1, tam);

    fim= clock();


    printf("\nInsertion Sort (V[%d]): %lf\n",tam,((double)(fim - inicio)/CLOCKS_PER_SEC));
    

    inicio= clock();

    heapsort(v1_copy, tam);

    fim= clock();

    
    printf("\nHeapSort (V[%d]): %lf\n\n\n",tam,((double)(fim - inicio)/CLOCKS_PER_SEC));

    
}


void calcula_colisoes_dispersao(int *div, int *dobra, int* mult, int* analise1, int* analise2, int *chaves, int n){

    int i;

    int cont = 0;

    for(i=0; i<100000; i++){
            div[i] = -1;
            dobra[i] = -1;
            mult[i] = -1;
            analise1[i] = -1;
            analise2[i] = -1;
    }

    int num_colisoes=0;

    for(i=0; i < n; i++){
            int aux = metodo_div(chaves[i], 100000);

            if(div[aux] == -1){
                div[aux] = chaves[i];
            }else{
                num_colisoes++;
            }
    }

    printf("Divisao: %d\n", num_colisoes);

    
    for(i=0, num_colisoes=0; i < n; i++){
            int tam;
            int *chave = int2Vector(chaves[i], &tam);

            int aux = metodo_dobra(chave, tam, 100000);

            if(dobra[aux] == -1){
                dobra[aux] = chaves[i];
            }else{
                num_colisoes++;
            }
    }

    printf("Dobra:  %d\n", num_colisoes);

    for(i=0, num_colisoes=0; i<n; i++){
            int aux = metodo_multiplicacao(chaves[i], 100000);

            if(mult[aux] == -1){
                mult[aux] = chaves[i];
            }else{
                num_colisoes++;
            }
    }

    printf("Multiplicacao: %d\n", num_colisoes);

    num_colisoes=0;
    num_colisoes = metodo_analise_digitos(chaves, n, analise1, 100000, 0);
            
    printf("Analise de digitos (1): %d\n", num_colisoes);

    num_colisoes=0;
    num_colisoes = metodo_analise_digitos(chaves, n, analise2, 100000, 1);
            
    printf("Analise de digitos (2): %d\n\n\n", num_colisoes);
}

int menu(int *v_heap){
    int i;
    int op;
    printf("\nVetor Heap atual: ");
    for(i = 0; i<TAM_VET;i++)
        printf("%d | ", v_heap[i]);

        printf("\n\n\n");

    printf("[1] Adicionar elemento\n");
    printf("[2] Remover elemento\n");
    printf("[3] Rodar heapsort\n");
    printf("[4] Rodar insertionsort\n");
    printf("[0] Executar testes\n");

    do{
        printf("\nOpcao: ");
        scanf("%d", &op);
    }while(op < 0 && op > 4);

    return op;
}
