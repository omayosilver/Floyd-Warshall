#include <stdio.h>
#include <omp.h>

// defining the number of vertices
#define nV 4
#define INF 999

void printMatrix(int matrix[][nV]);

// Implementing Floyd-Warshall algorithm with OpenMP parallelization
void floydWarshall(int graph[][nV]) {
    int matrix[nV][nV], i, j, k;

    #pragma omp parallel for private(i, j, k) shared(matrix, graph)
    for (i = 0; i < nV; i++)
        for (j = 0; j < nV; j++)
            matrix[i][j] = graph[i][j];

    // Adding vertices individually
    #pragma omp parallel for private(i, j, k) shared(matrix)
    for (k = 0; k < nV; k++) {
        #pragma omp parallel for private(i, j) shared(matrix)
        for (i = 0; i < nV; i++) {
            for (j = 0; j < nV; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
    printMatrix(matrix);
}

void printMatrix(int matrix[][nV]) {
    for (int i = 0; i < nV; i++) {
        for (int j = 0; j < nV; j++) {
            if (matrix[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int graph[nV][nV] = {{0, 3, INF, 5},
                         {2, 0, INF, 4},
                         {INF, 1, 0, INF},
                         {INF, INF, 2, 0}};

    // Set the number of threads for OpenMP
    omp_set_num_threads(4);

    // Measure the execution time
    double start_time = omp_get_wtime();

    floydWarshall(graph);

    // Print the execution time
    printf("Execution Time: %f seconds\n", omp_get_wtime() - start_time);

    return 0;
}
