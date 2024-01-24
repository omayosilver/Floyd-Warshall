// Floyd-Warshall Algorithm with MPI in C

#include <stdio.h>
#include <mpi.h>

// defining the number of vertices
#define nV 4
#define INF 999

void printMatrix(int matrix[][nV]);

// Implementing floyd warshall algorithm
void floydWarshall(int graph[][nV], int rank, int size) {
    int matrix[nV][nV], i, j, k;

    for (i = 0; i < nV; i++)
        for (j = 0; j < nV; j++)
            matrix[i][j] = graph[i][j];

    // Adding vertices individually
    for (k = 0; k < nV; k++) {
        for (i = 0; i < nV; i++) {
            for (j = 0; j < nV; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }

    if (rank == 0) {
        printMatrix(matrix);
    }
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


int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int graph[nV][nV] = {{0, 3, INF, 5},
                         {2, 0, INF, 4},
                         {INF, 1, 0, INF},
                         {INF, INF, 2, 0}};

    MPI_Barrier(MPI_COMM_WORLD);
    double startTime = MPI_Wtime();

    floydWarshall(graph, rank, size);

    MPI_Barrier(MPI_COMM_WORLD);
    double endTime = MPI_Wtime();

    if (rank == 0) {
        printf("Execution Time: %f seconds\n", endTime - startTime);
    }

    MPI_Finalize();
    return 0;
}

