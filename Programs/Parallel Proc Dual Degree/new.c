#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void   Read_vector(char* prompt, float local_v[], int local_n, int n,int my_rank, MPI_Comm comm);
float  Serial_dot(float x[], float y[], int m);
float  Parallel_dot(float local_x[], float local_y[], int local_n, MPI_Comm comm);
    
int main(void) {
    float*   local_x;
    float*   local_y;
    int      n;
    int      local_n;  // = n/p
    float    dot;
    int      p;
    int      my_rank;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == 0) {
        printf("Enter the order of the vectors\n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_n = n/p;

    local_x = malloc(local_n*sizeof(float));
    local_y = malloc(local_n*sizeof(float));
    Read_vector("the first vector", local_x, local_n, n, my_rank, comm);
    Read_vector("the second vector", local_y, local_n, n, my_rank, comm);

    dot = Parallel_dot(local_x, local_y, local_n, comm);

    if (my_rank == 0)
        printf("The dot product is %f\n", dot);

    free(local_x);
    free(local_y);
    MPI_Finalize();

    return 0;
}
void Read_vector(char* prompt,float local_v[],int local_n,int n,int my_rank,MPI_Comm comm) {
    int    i;
    float* temp;

    if (my_rank == 0) {
        temp = malloc(n*sizeof(float));
        printf("Enter %s\n", prompt);
        for (i = 0; i < n; i++)
            scanf("%f", &temp[i]);
        MPI_Scatter(temp, local_n, MPI_FLOAT, local_v, local_n, MPI_FLOAT,
           0, comm);
        free(temp);
    } else {
        MPI_Scatter(temp, local_n, MPI_FLOAT, local_v, local_n, MPI_FLOAT,
           0, comm);
    }
}
float Serial_dot(float x[],float y[],int  n) {
    int    i; 
    float  sum = 0.0;

    for (i = 0; i < n; i++)
        sum += x[i]*y[i];
    return sum;
}
float Parallel_dot(float local_x[],float local_y[],int local_n,MPI_Comm comm) {
	float  local_dot;
    float  dot = 0.0;

    local_dot = Serial_dot(local_x, local_y, local_n);
    MPI_Reduce(&local_dot, &dot, 1, MPI_FLOAT, MPI_SUM, 0, comm);
    return dot;
}
