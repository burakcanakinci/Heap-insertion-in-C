//Funcao que busca elemento em vetor
int busca(int *, int, int);

//Metodo da divisao
int metodo_div(int , int);

//Funcao auxiliar para adicionar 0's em vetor
int* add_zeros(int *, int , int);

//Metodo da dobra
int metodo_dobra(int *, int , int);

//Metodo da multiplicacao
int metodo_multiplicacao(int , int);

//Funcao auxiliar que gera vetor aleatoriamente dado um tamanho n
int* gerarVetor(int);

//Funcao que retorna o modulo
float modulo(float);

//Funcao que retorna a quantidade de digitos de um numero
int num_Digits(int);

//Funcao que calcula o desvio para um digito (posicao), entre varias chaves
//Pode receber 1 ou 0 (para alternar entre os somatorios)
double calcula_desvio_digito(int digit, int *, int , int , int);

//Escolhe o melhor desvio atual
int melhorDesvio(double *, int);

//Metodo da analise de digitos
int metodo_analise_digitos(int *, int, int*, int, int );

//Converte numero para vetor inteiro
int * int2Vector(int , int *);