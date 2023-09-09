#include <stdio.h> //Biblioteca fundamental do código, com funções e macros para entrada e saída de dados
#include <stdlib.h> //Biblioteca com funções para gerenciamento de memória, conversões, ordenações dentre outros. Aqui utilizada para funções como o "exit()" e o "system()"
#include <locale.h> //Biblioteca para lidar com localização e internacionalização de programas


int main(){
	setlocale(LC_ALL, "Portuguese"); //Definir a configuração regional, para aceitar caracteres especiais e acentuação 

    FILE *dados; //Ponteiro para arquivo
    FILE *destino;
    char linha[200]; //Variável para leitura do arquivo e armazenamento 
    int primeiraLinha = 1; //Variável para condição de desprezar primeira linha do arquivo, true

    dados=fopen("DadosEntrada.csv", "r"); //Abertura do arquivo em modo de somente leitura

    if(dados == NULL){ //Condição para encerramento do programa para casos em que o arquivo não existir
        printf("Erro ao abrir o arquivo.\n");
        exit(1); //Função para encerrar o programa de maneira controlada.
    }
    
    destino=fopen("SituacaoFinal.csv", "w+"); //Abertura do arquivo em modo de escrita e criação
    
	setlocale(LC_ALL, "C"); //Definir a configuração regional previamente em "C", de modo a não interferir nos cálculos a seguir

    while(fgets(linha, sizeof(linha), dados) != NULL){ //Loop para ler todas as linhas do arquivo
    	if(primeiraLinha){ //Condição para desprezar primeira linha do arquivo, true
    		primeiraLinha=0;  //False, condição não mais será executada
    		continue; //Pula o restante do lopp
    	
        char *nome = strtok(linha, ","); //Dividir (ou tokenizar) uma string usando como base as vírgulas 
        char *tel = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");
        char *nota1 = strtok(NULL, ",");
        char *nota2 = strtok(NULL, ",");
        
        float nota1f, nota2f;
        nota1f=strtof(nota1, NULL); //Converte uma string em um float
        nota2f=strtof(nota2, NULL);
        int media=(nota1f+nota2f)/2;
        
        if(((nota1f+nota2f)/2) >= 7){ //Condição para gravar condição de aprovado ou reprovado no novo arquivo
        	fprintf(destino, "%s, %d, APROVADO\n", nome, media);
		}
		else fprintf(destino, "%s, %d, REPROVADO\n", nome, media);
    }

	setlocale(LC_ALL, "Portuguese"); //Resetando configuração regional 

	printf("Seus cálculos foram executados com sucesso!\nA lista de alunos aprovados e reprovados já se encontra pronta em seus arquivos.\n\n");

	fclose(dados); //Fechamento de arquivos
	fclose(destino);
	system("pause"); //Pausar a execução do programa
	return 0;

}
