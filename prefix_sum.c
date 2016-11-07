#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>
#include<math.h>
#define ARRAY_SIZE 16
int main(int argc, char *argv[]){
	int me;
	int size;
	if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
		fprintf(stderr, "Unable to initialize MPI!\n");
		return -1;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(ARRAY_SIZE % size != 0 && me == 0){
		fprintf(stderr,"Array size must be multiple of mpi job size.\n");
		return -1;
	}
	MPI_Status status;
	int * array = (int *) malloc(sizeof(int) * ARRAY_SIZE);
	int * chunk = (int *) malloc(sizeof(int) * ARRAY_SIZE/size);
	int i = 0, logn=log2(size), d;
	int total_sum = 0;
	for(i = 0; i < ARRAY_SIZE; i++){
		array[i] = i+1;
		total_sum+=array[i];
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(array,ARRAY_SIZE/size,MPI_INT,chunk,ARRAY_SIZE/size,MPI_INT,0,MPI_COMM_WORLD);
	int sum = 0;
	int temp = 0;
	for(i = 0; i < ARRAY_SIZE/size; i++)
		sum += chunk[i];
	for(i=logn-1;i>=0;i--){
		d=pow(2,i);
		if(me>=d && me<2*d){
			MPI_Send(&sum, 1, MPI_INT, me-d,0,MPI_COMM_WORLD);
		}else if(me>=0 && me<d){
			MPI_Recv(&temp, 1, MPI_INT, me+d,0,MPI_COMM_WORLD,&status);
			sum += temp;
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	if(me == 0){
		fprintf(stdout,"Total: %d\n",sum);
		fprintf(stdout,"Correct Sum: %d\n",total_sum);
	}
	free(array);
	free(chunk);
	MPI_Finalize();
	return 0;
}
