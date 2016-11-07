#include<mpi.h>
#include<stdio.h>
#define N 10

int arr[N];
int main()
{
	int i,tag=0,rank,p;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(w,&p);
	MPI_Comm_rank(w,&rank);
	if(rank == 0)
	{
		printf("Enter the values\n");
		for(i=0;i<N;i++)
		{
			scanf("%i",&arr[i]);
		}

	}
	MPI_Bcast(arr,N,MPI_INT,0,w);
	int sum=0;
	for(i=rank;i<N;i+=p)
	{
		sum += arr[i];
	}
	printf("sum at %i is %i\n",rank,sum);
	if(rank != 0)
	{
		MPI_Send(&sum,1,MPI_INT,0,tag,w);
	}
	else
	{
		int temp;
		for(i=1;i<p;i++)
		{
			MPI_Recv(&temp,1,MPI_INT,i,tag,w,&status);
			sum += temp;
		}
		printf("The total sum is %i",sum);
	}
	MPI_Finalize();

	return 0;
}