#include<stdio.h>
#include<mpi.h>
#include<math.h>
#define N 50

int arr[N];

int main()
{
	int tag=0,rank,p,a,b,n;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(w,&rank);
	MPI_Comm_size(w,&p);

	if(rank == 0)
	{
		for(int i=0;i<p;i++)
			scanf("%i",&arr[i]);
	}

	MPI_Scatter(arr,1,MPI_INT,&a,1,MPI_INT,0,w);
	n = sqrt(p);
	for(int i=1;i<n;i++)
	{
		if(rank%n == i-1)
		{
			MPI_Send(&a,1,MPI_INT,rank+1,tag,w);
		}
		MPI_Barrier(w);
		if(rank%n == i)
		{
			MPI_Recv(&b,1,MPI_INT,rank-1,tag,w,&status);
			a += b;
		}
	}

	for(int i=1;i<n;i++)
	{
		if(rank/n == i-1 && rank%n == n-1)
		{
			MPI_Send(&a,1,MPI_INT,rank+n,tag,w);
		}
		MPI_Barrier(w);
		if(rank/n == i  && rank%n == n-1)
		{
			MPI_Recv(&b,1,MPI_INT,rank-n,tag,w,&status);
			a += b;
		}
	}

	for(int i=n-1;i>0;i--)
	{
		if(rank%n == i && rank/n > 0)
		{
			MPI_Send(&b,1,MPI_INT,rank-1,tag,w);
		}
		MPI_Barrier(w);
		if(rank%n == i-1 && rank/n > 0)
		{
			MPI_Recv(&b,1,MPI_INT,rank+1,tag,w,&status);
			a += b;
		}

	}
	printf("data at %i,%i is %i\n",rank/n,rank%n,a);
	MPI_Finalize();
	return 0;
}