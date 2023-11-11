#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

matriz_esparsa *cria_matriz_esparsa(int m, int n){
    matriz_esparsa *mat;
	mat = (matriz_esparsa *)malloc(sizeof(matriz_esparsa));

	if (!mat || m<=0 || n<=0){
        return 0;
	}

	mat->inicio = NULL;
	mat->fimLinha = NULL;
	mat->fimColuna = NULL;
	mat->m = m;
	mat->n = n;

	iniciaCabecas(mat);

	return mat;
}

matriz_esparsa *lerMatriz(){ 
    matriz_esparsa *mat;

    char linha[TAM_BUFFER];

    int m=0, n=0;
    int l=0, c=0;
    float valor=0.0;

    FILE *arquivo;

    arquivo = fopen("matrizA.txt","r");
    if (!arquivo){
      arquivo = fopen("arquivo.txt","w");
      fprintf(arquivo, "Erro ao abrir arquivo\n");
      fclose(arquivo);
      return NULL;
    }

    fgets(linha, TAM_BUFFER, arquivo);
    sscanf(linha, "%d %d", &m, &n);

    if (m<=0 || n<=0){
        return 0;
    }

    mat = cria_matriz_esparsa(m, n);

    while(fgets(linha, TAM_BUFFER, arquivo)){
        sscanf(linha, "%d %d %f", &l, &c, &valor);
        if (valor){
            insere(mat, l, c, valor);
        }
    }
    fclose(arquivo);
    return mat;
}

matriz_esparsa *lerMatrizB(){ 
    matriz_esparsa *mat;

    char linha[TAM_BUFFER];

    int m=0, n=0;
    int l=0, c=0;
    float valor=0.0;

    FILE *arquivo;

    arquivo = fopen("matrizB.txt","r");
    if (!arquivo){
      arquivo = fopen("arquivo.txt","w");
      fprintf(arquivo, "Erro ao abrir arquivo\n");
      fclose(arquivo);
      return NULL;
    }

    fgets(linha, TAM_BUFFER, arquivo); 
    sscanf(linha, "%d %d", &m, &n);

    if (m<=0 || n<=0){
        return 0;
    }

    mat = cria_matriz_esparsa(m, n);

    while(fgets(linha, TAM_BUFFER, arquivo)){
        sscanf(linha, "%d %d %f", &l, &c, &valor);
        if (valor){
            insere(mat, l, c, valor);
        }
    }
    fclose(arquivo);
    return mat;
}

int iniciaCabecas(matriz_esparsa *mat){ 
    int i=0;

    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0; 
    }

    cabeca->coluna = -1;
    cabeca->linha = -1;

    mat->inicio = cabeca;
    mat->fimLinha = cabeca;
    mat->fimColuna = cabeca;

    for (i = 1; i <= mat->n; i++){ 
        insereCabecaColuna(mat);
    }
    for (i = 1; i <= mat->m; i++){ 
        insereCabecaLinha(mat);
    }
    return 1;
}
int insereCabecaColuna(matriz_esparsa *mat){ 
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0; 
    }

    cabeca->coluna = -1;
    cabeca->linha = 0;

    mat->fimColuna->direita = cabeca;
    mat->fimColuna = cabeca;

    cabeca->direita = mat->inicio;
    cabeca->abaixo = cabeca;
    return 1;
}

int insereCabecaLinha(matriz_esparsa *mat){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;
    }

    cabeca->coluna = 0;
    cabeca->linha = -1;

    mat->fimLinha->abaixo = cabeca;
    mat->fimLinha = cabeca;

    cabeca->abaixo = mat->inicio;
    cabeca->direita = cabeca;

    return 1;
}

int insere(matriz_esparsa *mat, int linha, int coluna, float valor){
    int i;

    if (!mat || mat->m <= 0 || mat->n <= 0 || !valor){ 
        return 0;
    }
    if (linha>mat->m || coluna>mat->n || !valor || linha < 1 || coluna < 1){
        return 0;
    }

    tipo_celula *pCelula; 
    tipo_celula *pCelulaColuna; 
    tipo_celula *pCelulaLinha; 

    pCelula = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!pCelula){ 
        return 0;
    }

    pCelula->linha = linha;
    pCelula->coluna = coluna;
    pCelula->valor = valor;

    pCelulaLinha = mat->inicio->abaixo; 
    pCelulaColuna = mat->inicio->direita;

    for (i=0; i<linha-1; i++){ 
        pCelulaLinha = pCelulaLinha->abaixo; 
    }
    i=0;
    while (i<coluna && pCelulaLinha->direita->linha != -1){
        if (pCelulaLinha->direita->coluna > pCelula->coluna){ 
            pCelula->direita = pCelulaLinha->direita;
            pCelulaLinha->direita = pCelula;
        }
        else{
            pCelulaLinha = pCelulaLinha->direita; 
        }
        i++;
    }
    if (pCelulaLinha->direita->linha == -1){ 
        pCelula->direita = pCelulaLinha->direita; 
        pCelulaLinha->direita = pCelula; 
    }

    for (i = 0; i < coluna-1; i++){ 
        pCelulaColuna = pCelulaColuna->direita; 
    }
    i=0;
    while (i<linha && pCelulaColuna->abaixo->coluna != -1){ 
        if (pCelulaColuna->abaixo->linha > pCelula->linha){
            pCelula->abaixo = pCelulaColuna->abaixo;
            pCelulaColuna->abaixo = pCelula;
        }
        else{
            pCelulaColuna = pCelulaColuna->abaixo; 
        }
        i++;
    }
    if (pCelulaColuna->abaixo->coluna == -1){
        pCelula->abaixo = pCelulaColuna->abaixo; 
        pCelulaColuna->abaixo = pCelula; 
    }
    return 1;
}

int imprimeMatriz(matriz_esparsa *mat){
    int i, j;
    tipo_celula *pCelula;

    if (!mat || !mat->m || !mat->n){
        return 0;
    }

    pCelula = mat->inicio->abaixo;

    printf("\n");

    for (i = 1; i <= mat->m; i++){
        for (j = 1; j <= mat->n; j++){
            if (pCelula->direita->linha == i && pCelula->direita->coluna == j){
                pCelula = pCelula->direita;
                printf("  \t%0.2f   ", pCelula->valor);
            }
            else{
                printf("  \t%0.2f   ", 0.0F);
            }
        }
        printf("\n");
        pCelula = pCelula->direita->abaixo;
    }

    return 1;
}

int apagaMatriz(matriz_esparsa *mat){
    int i = 1;
    int j = 1;
    tipo_celula *pCelula, *aux;

    if (!mat || !mat->m || !mat->n){
        return 0;
    }

    pCelula = mat->inicio->abaixo;
    pCelula = pCelula->direita;

    for (i = 1; i <= mat->m; i++){
        for (j = 1; j <= mat->n; j++){
            if (pCelula->linha == i && pCelula->coluna == j){
                aux = pCelula;
                pCelula = pCelula->direita;
                free(aux);
            }
        }
        pCelula = pCelula->abaixo->direita;
    }

    pCelula = mat->inicio->direita;

    for (i = 0; i < mat->n; i++){ 
        aux = pCelula;
        pCelula = pCelula->direita;
        free(aux);
    }

    pCelula = mat->inicio->abaixo;
    for (i = 0; i < mat->m; i++){
        aux = pCelula;
        pCelula = pCelula->abaixo;
        free(aux);
    }

    pCelula = mat->inicio;
    free(pCelula);

    mat->fimColuna = mat->fimLinha = mat->inicio = NULL;
    mat->m = mat->n = 0;
    mat = NULL;

    return 1;
}

matriz_esparsa *somaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    int i, j;
    float soma;
    matriz_esparsa *matC;
    tipo_celula *pCelulaA, *pCelulaB;

    if (matA->m != matB->m || matA->n != matB->n){ 
        printf("\nMatrizes de Ordem diferente.\nSo eh possivel somar matrizes de mesma ordem\n");
        return NULL;
    }

    if (!matA || !matB || !matA->m || !matA->n){
        return NULL;
    }

    matC = cria_matriz_esparsa(matA->m, matB->n);

    pCelulaA = matA->inicio->abaixo;
    pCelulaB = matB->inicio->abaixo;

    for (i = 1; i <= matA->m; i++){
        for (j = 1; j <= matA->n; j++){
            if (j == pCelulaA->direita->coluna && j == pCelulaB->direita->coluna){
                soma = pCelulaA->direita->valor + pCelulaB->direita->valor;
                if (soma){
                    insere(matC, i, j, soma);
                }
                pCelulaA = pCelulaA->direita;
                pCelulaB = pCelulaB->direita;
            }
            else if (j == pCelulaA->direita->coluna){
                insere(matC, i, j, pCelulaA->direita->valor);
                pCelulaA = pCelulaA->direita;
            }
            else if (j == pCelulaB->direita->coluna){
                insere(matC, i, j, pCelulaB->direita->valor);
                pCelulaB = pCelulaB->direita;
            }
        }
        pCelulaA = pCelulaA->direita->abaixo;
        pCelulaB = pCelulaB->direita->abaixo;
    }

    return matC;
}

matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    int i=0, j=0, k=0;
    float total;
    matriz_esparsa *matC;

    if (matA->n != matB->m){ 
        printf("\nNao foi possivel multiplicar as matrizes\nnumero de colunas de A eh diferente do numero de linhas de B\n");
        return NULL;
    }

    if (!matA || !matB || !matA->m || !matA->n || !matB->n){
        return NULL;
    }

    matC = cria_matriz_esparsa(matA->m, matB->n); 

    for (i = 1; i <= matA->m; i++){
        for (j = 1; j <= matB->n; j++){
            total = 0;
            for (k = 1; k <= matA->n; k++){
                total += obtemElementoPeloIndice(matA,i,k) * obtemElementoPeloIndice(matB,k,j);
            }
            if (total){
                insere(matC,i,j,total);
            }
        }
    }
    return matC;
}

float obtemElementoPeloIndice(matriz_esparsa *mat, int linha, int coluna){
    tipo_celula *pCelula;
    int i = 0;

    pCelula = mat->inicio->direita;

    for (i = 0; i < coluna-1; i++){ 
        pCelula = pCelula->direita;
    }

    do{
        pCelula = pCelula->abaixo;
        if (pCelula->linha == linha){
            return pCelula->valor;
        }
    }while(pCelula->coluna != -1);

    return 0; 
}
