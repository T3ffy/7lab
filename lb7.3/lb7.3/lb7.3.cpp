// lb7.3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

void createAdjacencyList(Node** adjList, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2;
            if (edge == 1) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;

                newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = i;
                newNode->next = adjList[j];
                adjList[j] = newNode;
            }
        }
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void sortAdjacencyList(Node** adjList, int N) {
    for (int i = 0; i < N; i++) {
        int count = 0;
        Node* temp = adjList[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        if (count == 0) continue;  

        int* vertices = (int*)malloc(count * sizeof(int));
        temp = adjList[i];
        int index = 0;
        while (temp != NULL) {
            vertices[index++] = temp->vertex;
            temp = temp->next;
        }

        qsort(vertices, count, sizeof(int), compare);

        temp = adjList[i];
        index = 0;
        while (temp != NULL) {
            temp->vertex = vertices[index++];
            temp = temp->next;
        }

        free(vertices);
    }
}

void printAdjacencyList(Node** adjList, int N) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex + 1);
            temp = temp->next;
        }
		printf("//\n");
    }
}

void DFS(Node** adjList, int N, int* NUM, int v) {
    NUM[v] = 1;
    printf("%d ", v + 1);

    Node* temp = adjList[v];
    while (temp != NULL) {
        if (NUM[temp->vertex] == 0) {
            DFS(adjList, N, NUM, temp->vertex);
        }
        temp = temp->next;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));  

    int N;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Количество вершин должно быть положительным!\n");
        return 1;
    }

 
    Node** adjList = (Node**)malloc(N * sizeof(Node*));
    if (adjList == NULL) {
        printf("Ошибка выделения памяти для списка смежности\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        adjList[i] = NULL;
    }

    createAdjacencyList(adjList, N);
    sortAdjacencyList(adjList, N);
    printAdjacencyList(adjList, N);


    int* NUM = (int*)malloc(N * sizeof(int));
    if (NUM == NULL) {
        printf("Ошибка выделения памяти для массива NUM\n");

        for (int i = 0; i < N; i++) {
            Node* temp = adjList[i];
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
        }
        free(adjList);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    printf("\nРезультат обхода в глубину:\n");
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS(adjList, N, NUM, i);
        }
    }


    for (int i = 0; i < N; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adjList);
    free(NUM);
	scanf("%d");
    return 0;
}
