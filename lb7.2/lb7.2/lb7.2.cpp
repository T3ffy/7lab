// lb7.2.cpp: определяет точку входа для консольного приложения.
//

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
            G[i][j] = edge;
            G[j][i] = edge;
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

void DFS(int** G, int N, int* NUM, int v) {
    int* stack = (int*)malloc(N * sizeof(int));
    if (stack == NULL) {
        printf("Ошибка выделения памяти для стека\n");
        return;
    }
    
    int top = -1;
    stack[++top] = v;

    while (top != -1) {
        int vec = stack[top--];
        
        if (NUM[vec] == 0) {
            NUM[vec] = 1;
            printf("%d ", vec + 1);
            

            for (int i = N - 1; i >= 0; i--) {
                if (G[vec][i] == 1 && NUM[i] == 0) {
                    stack[++top] = i;
                }
            }
        }
    }
    
    free(stack);  
}

int main() {
    setlocale(LC_ALL, "");
    int N;

    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);


    if (N <= 0) {
        printf("Количество вершин должно быть положительным!\n");
        return 1;
    }


    int** G = (int**)malloc(N * sizeof(int*));
    if (G == NULL) {
        printf("Ошибка выделения памяти для матрицы\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        G[i] = (int*)malloc(N * sizeof(int));
        if (G[i] == NULL) {
            printf("Ошибка выделения памяти для строки матрицы\n");

            for (int j = 0; j < i; j++) {
                free(G[j]);
            }
            free(G);
            return 1;
        }
    }

    createG(G, N);
    printG(G, N);


    int* NUM = (int*)malloc(N * sizeof(int));
    if (NUM == NULL) {
        printf("Ошибка выделения памяти для массива NUM\n");

        for (int i = 0; i < N; i++) {
            free(G[i]);
        }
        free(G);
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    printf("\nРезультат обхода в глубину:\n");
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS(G, N, NUM, i);
        }
    }


    for (int i = 0; i < N; i++) {
        free(G[i]);
    }
    free(G);
    free(NUM);
	scanf("%d");
    return 0;
}
