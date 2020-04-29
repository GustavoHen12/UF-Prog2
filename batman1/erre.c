#include "erre.h"
//"AUXILIARES"

//Quicksort ----------------------------------------------
void troca(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

int particiona(float array[], int low, int high)
{
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


void ordena (float array[], int low, int high)
{
    if(low < high)
    {
        int index = particiona(array, low, high);

        ordena(array, low, index - 1);
        ordena(array, index + 1, high);
    }
}
//Fim Quicksort-----------------------------------------------------


//Funcoes
int inicia(tERRE *dados)
{
    dados->tam = 0;
    printf("1");
    (*dados).data = malloc(MAX * sizeof(float));
    if(dados->data == NULL) return 0;
    return 1;
}

int stringToErre(char *str, tERRE *dados)
{
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


int selecionaDigito(float numero, int dig)
{
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

float **alocaMatriz(int lin, int col)
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
    for(i = 0; i < col; i++){
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

int ultimoDigito(float numero)
{
    int num = numero;
    return num%10;
}

//imprime o dispositivo
//retorna uma matriz com os valores
float **ramoEfolhas(tERRE* dados, int quantRamos)
{
    int digitos = 2;
    if((quantRamos != 2) && (quantRamos != 5) && (quantRamos != 1))
        return NULL;
    printf("\nRamo e folhas\n");
    float **matriz;
    
    int linhas, colunas;
    linhas = (selecionaDigito(dados->data[dados->tam-1], digitos) -
              selecionaDigito(dados->data[0], digitos)) * quantRamos;
    colunas = dados->tam; //alterar para algo melhor
    printf(">%d \n", linhas);

    //aloca matriz
    matriz = alocaMatriz(linhas, colunas);
    if(matriz == NULL)
        return NULL;

    //inicia processo
    //coloca na matriz e imprime ao mesmo tempo
    int i = -1;
    int inicio = selecionaDigito(dados->data[0], digitos);
    int fim = selecionaDigito(dados->data[dados->tam-1], digitos);
    int ramo = 0;
    int limites[2] = {4, 9};
    while((i < dados->tam) && (inicio <= fim))
    {
        printf("%d |", inicio);
        while( (selecionaDigito(dados->data[i+1], digitos) == inicio) &&
               (ultimoDigito(dados->data[i+1]) <= limites[ramo]) &&
               (i < dados->tam))
        {
            i++;
            printf("%.2f ", dados->data[i]);
        }
        printf("\n");
        ramo++;
        if(ramo == quantRamos)
        {
            ramo = 0;
            inicio++;
       }
    }

    return matriz;
}


