#include <stdio.h> //Biblioteca fundamental do código, com funções e macros para entrada e saída de dados
#include <stdlib.h> //Biblioteca com funções para gerenciamento de memória, conversões, ordenações dentre outros
#include <string.h> //Biblioteca com funções para manipulação de strings
#include <locale.h> //Biblioteca para lidar com localização e internacionalização de programas

void swap(char **a, char **b) {  //Função para troca. Usando ponteiros de ponteiros, de modo que permita a troca de posição das strings
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int particao(char *vetor[], int inf, int sup) { //Função para encontrar a posição correta do pivô no vetor e particioná-lo
    char *pivot = vetor[sup]; //Escolhendo o último elemento como pivô
    int i = (inf - 1); // O índice do menor elemento 

    for (int j = inf; j <= sup - 1; j++) {
        if (strcmp(vetor[j], pivot) < 0) { //Compara as duas strings, se a string 'vetor[j]' for menor que a string 'pivot' a condição é verdadeira 
            i++;
            swap(&vetor[i], &vetor[j]); //Chamando função para troca (swap) entre os índices
        }
    }
    swap(&vetor[i + 1], &vetor[sup]); //Chamando função para troca (swap) entre os índices
    return (i + 1); //Retornando índice 
}

void quicksort(char *vetor[], int inf, int sup) {
    if (inf < sup) {
        int pi = particao(vetor, inf, sup); //Chamando a função 'particao' para encontrar o pivô e particioná-lo
        quicksort(vetor, inf, pi - 1); //Chamando recursivamente a função 'quicksort' a esquerda do pivô
        quicksort(vetor, pi + 1, sup); //Chamando recursivamente a função 'quicksort' a direita do pivô
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese"); //Definir a configuração regional, para aceitar caracteres especiais e acentuação 
	
    char *arr[20] = {"maca", "banana", "pera", "uva", "laranja", "abacaxi", "limão", "manga", "abacate", "kiwi", "cereja", "morango", "pêssego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"};
    int n = sizeof(arr) / sizeof(arr[0]); //Calculando o tamanho do vetor

    printf("Vetor desordenado:\n");
    for (int i = 0; i < n; i++) { //Loop para imprimir vetor desordenado
        printf("%s ", arr[i]);
    }
    
    printf("\n\nPressione qualquer tecla para ordenar o vetor acima!\n\n");
    system("pause");

    quicksort(arr, 0, n - 1); //Chamando função para ordenador vetor 

    printf("\nVetor ordenado:\n"); //Loop para imprimir vetor ordenado
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    
    printf("\n\n");
    system("pause");
    return 0;
}
