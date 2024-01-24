# Floyd-Warshall
This is a course test for parallel programming by Dr Yulan Jan 2024

In this experiment we performed the Floyd-Warshall algorithm using parallel programming with **OpenMP and MPI**

**How to Perform the Experiment:**

1. For OpenMP program floyd.c
   -compile with: gcc -fopenmp flody.c -o flody
   - Run with: ./flody
  
3. For MPI program floydmpi.c
   - compile with: mpicc flodympi.c -o flodympi
   - Run with: mpirun -np 4 ./flodympi           // 4 is the Number of processors
