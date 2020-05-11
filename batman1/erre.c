#include "erre.h"
//"AUXILIARES"

//Quicksort
static int particiona(float array[], int low, int high);
static void troca(float* a, float* b);
static void ordena (float array[], int low, int high);

//recebe um numero e uma quantidade de digitos
//quebra o numero recebido e retona o resultado
//nao considera a parte decimal do float
//ex: 122.345(numero), 2(dig) => |12|2.345 => retorna 12
static int selecionaDigito(float numero, int dig);

//retona o ponteiro para uma matriz de lin linha
//e col colunas
//a matriz e preechida com '0'
static float **alocaMatriz(int lin, int col);

static int ultimoDigito(float numero);

//Funcoes
int inicia(tERRE *dados){
    dados->tam = 0;
    (*dados).data = malloc(MAX * sizeof(float));
    if(dados->data == NULL) return 0;
 
    return 1;
}

int stringToErre(char *str, tERRE *dados){
    char num[10];//tamanho maximo de digitos
    int i = 0, j = 0, tam = 0;

    //converte todos os numeros para float
    while(str[i] != '\0'){
        j = 0;
        //enquanto for numero ou ponto
        while((((str[i] >= 48) && (str[i] <= 57)) || (str[i] == 36)) && (str[i] != '\0')){
            //coloca o numero em num
            num[j] = str[i];
            j++;
            i++;
        }
        num[j] = '\0';
        //se pegou algum numero
        if(j > 0){
            //convete para float e adiciona nos dados
            dados->data[dados->tam] = atof(num);
            dados->tam++;
            tam++;
            //se precisar alocar mais memoria
            if(tam > MAX){
                dados->data = realloc(dados->data, (dados->tam + MAX) * sizeof(float));
                tam = 0;
            }
        }
        i++;
    }

    //ordena os dados
    ordena(dados->data, 0, dados->tam);

    return 1;
}

//imprime o dispositivo
//retorna uma matriz com os valores
float **ramoEfolhas(tERRE* dados, int quantRamos){
    int digitos = 2;
    if((quantRamos != 2) && (quantRamos != 5) && (quantRamos != 1))
        return NULL;
    printf("\n**** Ramo e folhas ****\n");
    float **matriz;
    
    int inicio = selecionaDigito(dados->data[0], digitos);
    int fim = selecionaDigito(dados->data[dados->tam-1], digitos);
    
    int linhas, colunas;
    linhas = (fim - inicio + 1) * quantRamos;
    colunas = dados->tam; //alterar para algo melhor
    printf("> %d, %d \n", linhas, dados->tam);

    //aloca matriz
    matriz = alocaMatriz(linhas, colunas);
    if(matriz == NULL)
        return NULL;

    //inicia processo
    //coloca na matriz e imprime ao mesmo tempo
    int i = -1, j = 0, k = -1;
    int ramo = 0;
    int limites[2] = {4, 9};
    while((i < dados->tam) && (inicio <= fim))
    {
        printf("%d |", inicio);
        matriz[j][k] = inicio;
        while( (selecionaDigito(dados->data[i+1], digitos) == inicio) &&
               (ultimoDigito(dados->data[i+1]) <= limites[ramo]) &&
               (i < dados->tam))
        {
            i++; k++;
            printf("%.2f ", dados->data[i]);
            matriz[j][k] = dados->data[i];
        }
        printf("\n");
        j++;
        ramo++;
        if(ramo == quantRamos)
        {
            ramo = 0;
            inicio++;
       }
    }
    
    return matriz;
}

//imprime o dispositivo
//retorna uma matriz com os valores na ordem:
//minino, 1quartil, mediana, 3quartil, maximo
//a primeira coluna sao as alturas e a segunda o valor
float **cincoNumeros(tERRE* dados)
{
    printf("\n**** 5 numeros ****\n");
    float** matriz;
    matriz = alocaMatriz(5, 2);
    if(matriz == NULL)
        return NULL;

    //MINIMO
    matriz[0][0] = 1;//altura
    matriz[0][1] = dados->data[0];//valor

    //MAXIMO
    matriz[4][0] = 1;//altura
    matriz[4][1] = dados->data[dados->tam - 1];

    
    int metade = dados->tam / 2;
    //MEDIANA (caso impar)
    if((dados->tam % 2) != 0){
        matriz[2][0] = (dados->tam / 2.0) + 1;
        matriz[2][1] = dados->data[metade+1];
    }
    //MEDIANA (caso par)
    else {
        matriz[2][0] = (dados->tam + 1) / 2.0;
        matriz[2][1] = (dados->data[metade] + dados->data[metade+1]) / 2;
    }

    if((dados->tam % 4) != 0){
        int altura = (dados->tam / 4) + 1;
        matriz[1][0] = altura;
        matriz[3][0] = altura;

        //1 QUARTIL (caso impar)
        matriz[1][1] = dados->data[altura];
 
        //3 QUARTIL (caso impar)
        altura = altura + metade;
        matriz[3][1] = (dados->data[altura]);
    }
    else{
        int altura = (dados->tam + 2) / 4;
        matriz[1][0] = (dados->tam + 2) / 4.0;
        matriz[3][0] = (dados->tam + 2) / 4.0;
        //1 QUARTIL (caso par)

        matriz[1][1] = (dados->data[altura] + dados->data[altura+1]) / 2;

        //3 QUARTIL (caso par)
        altura = altura + metade;
        matriz[3][1] = (dados->data[altura] + dados->data[altura+1]) / 2;;
        
    }

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 2; j++)
            printf("%.2f ", matriz[i][j]);
        printf("\n");
    }
    
    return matriz; 
}


//Quicksort ----------------------------------------------
static void troca(float* a, float* b){
    float t = *a;
    *a = *b;
    *b = t;
}

static int particiona(float array[], int low, int high){
    float pivo = array[high];

    int i = low - 1;

    for(int j = low; j <= high; j++){
        if(array[j] < pivo){
            i++;
            troca(&array[j], &array[i]);
         }
    }

    troca(&array[i+1], &array[high]);
    return i+1;
}

static void ordena (float array[], int low, int high){
    if(low < high)
    {
        int index = particiona(array, low, high);

        ordena(array, low, index - 1);
        ordena(array, index + 1, high);
    }
}
//Fim Quicksort-----------------------------------------------------

static int selecionaDigito(float numero, int dig){
    //converte para inteiro
    int num = numero;
    //faz a mascara
    int masck = 1;
    int i = 0;
    while(i < dig){
        masck *= 10;
        i++;
    }
    masck--;
    //pega os digitos
    while((masck - num) < 0){
        num = num/10;
    }

    return num;
}

static float **alocaMatriz(int lin, int col)
{
    float ** mat;
    int i, j;
    //verifica se os parametros sao validos
    if((lin < 1) || (col < 1))
        return NULL;

    //aloca matriz
    mat = malloc (lin * sizeof(float*));
    if(mat == NULL)
        return NULL;
    for(i = 0; i < lin; i++){
        mat[i] = malloc(col * sizeof(float));
        if(mat[i] == NULL)
            return NULL;
    }
    
    //zera matriz
    for(i = 0; i < lin; i++)
        for(j = 0; j < col; j++)
            mat[i][j] = 0;
   
    return mat;
}

static int ultimoDigito(float numero)
{
    int num = numero;
    return num%10;
}
