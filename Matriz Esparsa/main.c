#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matriz.h"

int main(){
    int opcao = 0;
    int mat = 0;
    char nome[TAM_BUFFER];

    matriz_esparsa *matrizA = NULL;
    matriz_esparsa *matrizB = NULL;
    matriz_esparsa *matrizC = NULL;

    do{ 
        LIMPA_TELA();
        printf("\nMATRIZ ESPARSA\n\n");
        printf("\n1 - Ler Matriz");
        printf("\n2 - Imprimir Matriz");
        printf("\n3 - Apagar Matriz");
        printf("\n4 - Somar Matrizes");
        printf("\n5 - Multiplicar Matrizes");
        printf("\n6 - Sair");
        printf("\n\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:{ 
                LIMPA_TELA();
                printf("Digite 1 para ler a matriz A ou 2 para ler a matriz B: ");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if (matrizA){
                            apagaMatriz(matrizA);
                        }
                        matrizA = lerMatriz();
                        if(matrizA == NULL){
                            printf("Erro ao abrir arquivo");
                        }
                        break;
                    }
                    case 2:{
                        if (matrizB){
                            apagaMatriz(matrizB);
                        }
                        matrizB = lerMatrizB(nome);
                        if(matrizB == NULL){
                            printf("Erro ao abrir arquivo");
                        }
                        break;
                    }
                }
                PAUSA_TELA();
                break;
            }
            case 2:{
                LIMPA_TELA();
                printf("Qual matriz deseja imprimir ?\n1 - Matriz A\n2 - Matriz B\n3 - Matriz C\n");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if (!matrizA){
                            break;
                        }
                        imprimeMatriz(matrizA);
                        break;
                    }
                    case 2:{
                        if (!matrizB){
                            break;
                        }
                        imprimeMatriz(matrizB);
                        break;
                    }
                    case 3:{
                        if (!matrizC){
                            break;
                        }
                        imprimeMatriz(matrizC);
                        break;
                    }
                }
                PAUSA_TELA();
                break;
            }
            case 3:{
                LIMPA_TELA();
                printf("Qual matriz deseja apagar ?\n1 - Matriz A\n2 - Matriz B\n3 - Matriz C\n");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if(matrizA){
                            apagaMatriz(matrizA);
                        }
                        break;
                    }
                    case 2:{
                        if (matrizB){
                            apagaMatriz(matrizB);
                        }
                        break;
                    }
                    case 3:{
                        if (matrizC){
                            apagaMatriz(matrizC);
                        }
                        break;
                    }
                }
                PAUSA_TELA();
                break;
            }
            case 4:{ 
                LIMPA_TELA();
                if (matrizA && matrizB){
                    printf("A + B serao somadas, e o resultado ira para a matriz C\n");
                    matrizC = somaMatriz(matrizA, matrizB);
                }
                PAUSA_TELA();
                break;
            }
            case 5:{ 
                LIMPA_TELA();
                if (matrizA && matrizB){
                    printf("A * B serao multiplicados, e o resultado ira para a matriz C\n");
                    matrizC = multiplicaMatriz(matrizA, matrizB);
                }
                PAUSA_TELA();
                break;
            }
           
        }

    }while(opcao != 6);

    printf("\n\n");

    PAUSA_TELA();
    return 0;
}
