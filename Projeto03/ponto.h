#ifndef PONTO_H //Bloqueio de inclusão condicional, evitando que o conteúdo do arquivo seja incluído mais de uma vez
#define PONTO_H //Define um símbolo PONTO_H para indicar que o arquivo de cabeçalho foi incluído

typedef struct { //Definindo TAD ponto que representa um ponto com coordenadas X e Y
    float X;
    float Y;
} Ponto;

typedef struct { //Definindo TAD Poligono que representa um polígono com um número de vértices e um array de pontos (vertices) que armazena as coordenadas dos vértices.
    int numVertices;
    Ponto *vertices;
} Poligono;

float calcularArea(Poligono *poligono); //Permitindo que outros arquivos chamem a função

#endif //Fim do bloqueio de inclusão condicional
