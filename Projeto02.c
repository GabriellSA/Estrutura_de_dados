#include <stdio.h> //Biblioteca fundamental do c�digo, com fun��es e macros para entrada e sa�da de dados
#include <stdlib.h> //Biblioteca com fun��es para gerenciamento de mem�ria, convers�es, ordena��es dentre outros
#include <string.h> //Biblioteca com fun��es para manipula��o de strings
#include <locale.h> //Biblioteca para lidar com localiza��o e internacionaliza��o de programas

void swap(char **a, char **b) {  //Fun��o para troca. Usando ponteiros de ponteiros, de modo que permita a troca de posi��o das strings
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int particao(char *vetor[], int inf, int sup) { //Fun��o para encontrar a posi��o correta do piv� no vetor e particion�-lo
    char *pivot = vetor[sup]; //Escolhendo o �ltimo elemento como piv�
    int i = (inf - 1); // O �ndice do menor elemento 

    for (int j = inf; j <= sup - 1; j++) {
        if (strcmp(vetor[j], pivot) < 0) { //Compara as duas strings, se a string 'vetor[j]' for menor que a string 'pivot' a condi��o � verdadeira 
            i++;
            swap(&vetor[i], &vetor[j]); //Chamando fun��o para troca (swap) entre os �ndices
        }
    }
    swap(&vetor[i + 1], &vetor[sup]); //Chamando fun��o para troca (swap) entre os �ndices
    return (i + 1); //Retornando �ndice 
}

void quicksort(char *vetor[], int inf, int sup) {
    if (inf < sup) {
        int pi = particao(vetor, inf, sup); //Chamando a fun��o 'particao' para encontrar o piv� e particion�-lo
        quicksort(vetor, inf, pi - 1); //Chamando recursivamente a fun��o 'quicksort' a esquerda do piv�
        quicksort(vetor, pi + 1, sup); //Chamando recursivamente a fun��o 'quicksort' a direita do piv�
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese"); //Definir a configura��o regional, para aceitar caracteres especiais e acentua��o 
	
    char *arr[20] = {"maca", "banana", "pera", "uva", "laranja", "abacaxi", "lim�o", "manga", "abacate", "kiwi", "cereja", "morango", "p�ssego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"};
    int n = sizeof(arr) / sizeof(arr[0]); //Calculando o tamanho do vetor

    printf("Vetor desordenado:\n");
    for (int i = 0; i < n; i++) { //Loop para imprimir vetor desordenado
        printf("%s ", arr[i]);
    }
    
    printf("\n\nPressione qualquer tecla para ordenar o vetor acima!\n\n");
    system("pause");

    quicksort(arr, 0, n - 1); //Chamando fun��o para ordenador vetor 

    printf("\nVetor ordenado:\n"); //Loop para imprimir vetor ordenado
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    
    printf("\n\n");
    system("pause");
    return 0;
}
