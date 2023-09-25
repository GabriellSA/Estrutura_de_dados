#include "ponto.h" //Incluido o cabeçalho ponto.h, que possui TAD ponto e a TAD Poligono

float calcularArea(Poligono *poligono) {
    float area = 0;
    int i, j;

    for (i = 0; i < poligono->numVertices; i++) { //Inicia um loop que percorre todos os vértices do polígono. poligono->numVertices é o número de vértices do polígono.
        j = (i + 1) % poligono->numVertices; //Calcula o índice j do próximo vértice no polígono.
        area += (poligono->vertices[i].X + poligono->vertices[j].X) * //calcula a contribuição da aresta entre os vértices i e j para a área total do polígono usando a fórmula do determinante
                (poligono->vertices[i].Y - poligono->vertices[j].Y);
    }

    return area / 2.0; //Retorna a área calculada dividida por 2.0, uma vez que a fórmula do determinante produz duas vezes a área real. 
}
