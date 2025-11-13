
#include "stdafx.h"
// lb7.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

void createG(int** G, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2;
            G[j][i]=G[i][j] = edge;
        }
    }

    for (int i = 0; i < N; i++) {
        G[i][i] = 0;
    }
}

void printG(int** G, int N) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}
void findIsolatedVertices(int** G, int N) {
    printf("\nИзолированные вершины: ");
    
    int isolatedCount = 0;
    for (int v = 0; v < N; v++) {
        int hasEdges = 0;
        for (int u = 0; u < N; u++) {
            if (G[v][u] == 1) {  
                hasEdges = 1;
                break;
            }
        }
        
        if (!hasEdges) { 
            printf("%d ", v + 1);  
            isolatedCount++;
        }
    }
    
    if (isolatedCount == 0) {
        printf("отсутствуют");
    }
    printf("\n");
}

int DFS(int** G, int N, int* NUM, int v) {

    NUM[v] = 1;


    int has_edges = 0;
    for (int i = 0; i < N; i++) {
        if (G[v][i] == 1) {
            has_edges = 1;
            break;
        }
    }

	
    if (!has_edges) {
		return 1;
    }

    printf("%d ", v + 1);



    for (int i = 0; i < N; i++) {
        if (G[v][i] == 1 && NUM[i] == 0) {
            DFS(G, N, NUM, i);
        }
    }
}


int main() {
	srand(time(0));
    setlocale(LC_ALL, "");
    int N, current;

    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    int** G = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        G[i] = (int*)malloc(N * sizeof(int));
    }
    createG(G, N);
    printG(G, N);

    printf("Введите текущую вершину (1–%d): ", N);
    scanf("%d", &current);
    current--;

    if (current < 0 || current >= N) {
        printf("Некорректный номер вершины!\n");
        return 1;
    }

    int* NUM = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    printf("\nРезультат обхода в глубину:\n");
    if (NUM[current] == 0) {
        DFS(G, N, NUM, current);
    }

    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS(G, N, NUM, i);
        }
    }
	findIsolatedVertices(G, N);
    for (int i = 0; i < N; i++) {
        free(G[i]);
    }
    free(G);
    free(NUM);

    scanf("%d");  
    return 0;
}



