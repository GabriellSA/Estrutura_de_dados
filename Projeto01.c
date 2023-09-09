#include <stdio.h> //Biblioteca fundamental do c�digo, com fun��es e macros para entrada e sa�da de dados
#include <stdlib.h> //Biblioteca com fun��es para gerenciamento de mem�ria, convers�es, ordena��es dentre outros. Aqui utilizada para fun��es como o "exit()" e o "system()"
#include <locale.h> //Biblioteca para lidar com localiza��o e internacionaliza��o de programas


int main(){
	setlocale(LC_ALL, "Portuguese"); //Definir a configura��o regional, para aceitar caracteres especiais e acentua��o 

    FILE *dados; //Ponteiro para arquivo
    FILE *destino;
    char linha[200]; //Vari�vel para leitura do arquivo e armazenamento 
    int primeiraLinha = 1; //Vari�vel para condi��o de desprezar primeira linha do arquivo, true

    dados=fopen("DadosEntrada.csv", "r"); //Abertura do arquivo em modo de somente leitura

    if(dados == NULL){ //Condi��o para encerramento do programa para casos em que o arquivo n�o existir
        printf("Erro ao abrir o arquivo.\n");
        exit(1); //Fun��o para encerrar o programa de maneira controlada.
    }
    
    destino=fopen("SituacaoFinal.csv", "w+"); //Abertura do arquivo em modo de escrita e cria��o
    
	setlocale(LC_ALL, "C"); //Definir a configura��o regional previamente em "C", de modo a n�o interferir nos c�lculos a seguir

    while(fgets(linha, sizeof(linha), dados) != NULL){ //Loop para ler todas as linhas do arquivo
    	if(primeiraLinha){ //Condi��o para desprezar primeira linha do arquivo, true
    		primeiraLinha=0;  //False, condi��o n�o mais ser� executada
    		continue; //Pula o restante do lopp
    	
        char *nome = strtok(linha, ","); //Dividir (ou tokenizar) uma string usando como base as v�rgulas 
        char *tel = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");
        char *nota1 = strtok(NULL, ",");
        char *nota2 = strtok(NULL, ",");
        
        float nota1f, nota2f;
        nota1f=strtof(nota1, NULL); //Converte uma string em um float
        nota2f=strtof(nota2, NULL);
        int media=(nota1f+nota2f)/2;
        
        if(((nota1f+nota2f)/2) >= 7){ //Condi��o para gravar condi��o de aprovado ou reprovado no novo arquivo
        	fprintf(destino, "%s, %d, APROVADO\n", nome, media);
		}
		else fprintf(destino, "%s, %d, REPROVADO\n", nome, media);
    }

	setlocale(LC_ALL, "Portuguese"); //Resetando configura��o regional 

	printf("Seus c�lculos foram executados com sucesso!\nA lista de alunos aprovados e reprovados j� se encontra pronta em seus arquivos.\n\n");

	fclose(dados); //Fechamento de arquivos
	fclose(destino);
	system("pause"); //Pausar a execu��o do programa
	return 0;

}
