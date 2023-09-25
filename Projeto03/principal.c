#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

int main() {
    const char *nomeArquivo = "vertices.txt"; // Nome do arquivo de entrada
    FILE *arquivo;
    int numVertices;
    Poligono poligono;

    arquivo = fopen(nomeArquivo, "r"); //Abrindo arquivo para leitura

    if (arquivo == NULL) { //Verificando se o arquivo não se encontra sem dados
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit;
    }

    fscanf(arquivo, "%d", &numVertices); //Lendo o número de vértices que consta no arquivo

    poligono.numVertices = numVertices; //Atribuindo o valor de numVertices à variável numVertices da estrutura poligono, indicando o número de vértices no polígono
    poligono.vertices = (Ponto *)malloc(numVertices * sizeof(Ponto)); //Alocando dinamicamente memória para armazenar os vértices do polígono

    if (poligono.vertices == NULL) { //Verificando se a alocação de memória foi bem-sucedida.
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        exit;
    }

    for (int i = 0; i < numVertices; i++) { //percorrendo todos os vértices do polígono
        fscanf(arquivo, "%f %f", &poligono.vertices[i].X, &poligono.vertices[i].Y); // Lendo as coordenadas X e Y de cada vértice do arquivo e armazenando nas variáveis X e Y do vértice correspondente no TAD poligono
    }

    fclose(arquivo); //Fechando o arquivo

    float area = calcularArea(&poligono); //Calculando a área

    printf("Área do polígono: %.2f\n", area);

    free(poligono.vertices); //Liberando a memória alocada

    printf("\n\n");
    system("pause");
    return 0;
}
