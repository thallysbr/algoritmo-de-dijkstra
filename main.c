#include <stdio.h>
#include <stdlib.h>

#define VERTICES 6
#define INFINITO 30000

// Imprime a matriz de adjacência
void printMatriz(int grafo[VERTICES][VERTICES], int numeroVertices) {
    int i, j;
    printf("\nMatriz de Adjacencia:\n");
    printf("  ");
    
    // Imprime o cabeçalho
    for (i = 0; i < numeroVertices; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    
    // Imprime as linhas da matriz
    for (i = 0; i < numeroVertices; i++) {
        printf("%c ", 'A' + i); // Título da linha
        for (j = 0; j < numeroVertices; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

// Imprime o caminho mais curto de um vértice para outro vértice (identificando pelos indices as linhas e coluna)
void imprimirCaminho(int pai[], int j, int parteDe) {
    if (pai[j] == -1) {
        printf("%d", j + parteDe);
        return;
    }

    imprimirCaminho(pai, pai[j], parteDe);
    printf(" -> %d", j + parteDe);
}

// Imprime o caminho mais curto: identificando pelos indices ou numericamente (a partir de 1) as linhas e coluna
void imprimirCaminhoMaisCurto(int distancias[], int pai[], int origem, int destino, int parteDe) {
    if(parteDe == 1){
        printf("\n\nImprime o caminho mais curto (identificando numericamente, a partir de 1, as linhas e coluna)\n");
    } else {
        printf("\n\nImprime o caminho mais curto (identificando pelos indices as linhas e coluna)\n");
    }
    printf("\nDistancia do Vertice %d para o Vertice %d: %d\n", origem + parteDe, destino + parteDe, distancias[destino]);
    printf("Caminho: ");
    imprimirCaminho(pai, destino, parteDe);
    printf("\n");
}

// Imprime o caminho mais curto de um vértice para outro vértice (identificando pelas letras as linhas e coluna)
void imprimirCaminhoLetras(int pai[], int j) {
    if (pai[j] == -1) {
        printf("%c", 'A' + j);
        return;
    }

    imprimirCaminhoLetras(pai, pai[j]);
    printf(" -> %c", 'A' + j);
}

// Imprime o caminho mais curto (identificando pelas letras as linhas e coluna)
void imprimirCaminhoMaisCurtoLetras(int distancias[], int pai[], int origem, int destino) {
    printf("\n\nImprime o caminho mais curto (identificando pelas letras as linhas e coluna)\n");
    printf("\nDistancia do Vertice %c para o Vertice %c: %d\n", 'A' + origem, 'A' + destino, distancias[destino]);
    printf("Caminho: ");
    imprimirCaminhoLetras(pai, destino);
    printf("\n");
}

// Função para encontrar o vértice com a menor distância que ainda não foi incluído na árvore de caminho mais curto
int encontrarMenorDistancia(int distancias[], int conjuntoCaminhoMaisCurto[]) {
    int menor = INFINITO, indiceDoMenor;

    for (int vertice = 0; vertice < VERTICES; vertice++) {
        if (conjuntoCaminhoMaisCurto[vertice] == 0 && distancias[vertice] <= menor) {
            menor = distancias[vertice];
            indiceDoMenor = vertice;
        }
    }

    return indiceDoMenor;
}

// Função que implementa o algoritmo de Dijkstra para encontrar o caminho mais curto a partir de uma única origem
void dijkstra(int grafo[VERTICES][VERTICES], int origem, int destino) {
    int distancias[VERTICES]; // Array que armazenará a menor distância de origem para cada vértice
    int conjuntoCaminhoMaisCurto[VERTICES]; // Conjunto que indica se o vértice já está no caminho mais curto
    int pai[VERTICES]; // Array para armazenar o caminho construído

    // Inicia as distancias como INFINITO (numero grande) e nenhum vértice no conjunto do caminho mais curto
    for (int i = 0; i < VERTICES; i++) {
        pai[i] = -1;
        distancias[i] = INFINITO;
        conjuntoCaminhoMaisCurto[i] = 0;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    distancias[origem] = 0;

    // Processo para encontrar o menor caminho para todos os vértices
    for (int contagem = 0; contagem < VERTICES - 1; contagem++) {
        int u = encontrarMenorDistancia(distancias, conjuntoCaminhoMaisCurto);

        conjuntoCaminhoMaisCurto[u] = 1;

        for (int v = 0; v < VERTICES; v++) {
            if (!conjuntoCaminhoMaisCurto[v] && grafo[u][v] && distancias[u] != INFINITO && distancias[u] + grafo[u][v] < distancias[v]) {
                pai[v] = u;
                distancias[v] = distancias[u] + grafo[u][v];
            }
        }
    }

    // Imprime o caminho mais curto
    // Partindo de 0
    imprimirCaminhoMaisCurto(distancias, pai, origem, destino, 0);
    // Partindo de 1
    imprimirCaminhoMaisCurto(distancias, pai, origem, destino, 1);
    // Partindo de A
    imprimirCaminhoMaisCurtoLetras(distancias, pai, origem, destino);
}

int main() {
    int grafo[VERTICES][VERTICES] = {
        {0, 1, 4, 0, 0, 0},
        {1, 0, 4, 2, 7, 0},
        {4, 4, 0, 3, 5, 0},
        {0, 2, 3, 0, 4, 6},
        {0, 7, 5, 4, 0, 7},
        {0, 0, 0, 6, 7, 0}
    };

    // print da matriz usando printaMatriz
    printMatriz(grafo, VERTICES);

    // Origem e destino estão configurados de 0 a 5 (que seria da coluna 1 a coluna 6, ou da coluna A a coluna F)
    int origem = 0;  // Origem (no caso de 0 é o vértice A)
    int destino = 5;  // Destino (no caso de 5 é o vértice F)

    // Chamada da função de Dijkstra para encontrar o caminho mais curto
    dijkstra(grafo, origem, destino);

    printf("\nPressione Enter para sair do programa...");
    getchar();

    return 0;
}