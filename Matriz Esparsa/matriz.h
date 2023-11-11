#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct t_celula{
    struct t_celula *direita, *abaixo;
    int linha, coluna;
    float valor;
}tipo_celula;

typedef struct{
    int m, n;
    tipo_celula *inicio, *fimLinha, *fimColuna;
}tipo_matriz_esparsa;

typedef tipo_matriz_esparsa matriz_esparsa;

matriz_esparsa *cria_matriz_esparsa(int m, int n);
int iniciaCabecas(matriz_esparsa *mat);
int insereCabecaLinha(matriz_esparsa *mat);
int insereCabecaColuna(matriz_esparsa *mat);

int insere(matriz_esparsa *mat, int linha, int coluna, float valor);
int imprimeMatriz(matriz_esparsa *mat);
int apagaMatriz(matriz_esparsa *mat);
matriz_esparsa *somaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);
matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);

float obtemElementoPeloIndice(matriz_esparsa *mat, int linha, int coluna);

#define TAM_BUFFER 255
#define LIMPA_VARIAVEIS(_string, _tamanho) memset(_string,'\0',_tamanho)
#define TAM_NUMERO 10

matriz_esparsa *lerMatriz();
matriz_esparsa *lerMatrizB();

#define naoFazNada() ;
#define LIMPA_BUFFER() scanf("%*[^\n]"); getchar()
#define LIMPA_TELA() system("cls")
#define PAUSA_TELA() system("pause")

#endif 
