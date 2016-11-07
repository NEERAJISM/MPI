#include<mpi.h>
#include<stdio.h>

#define N 50
int arr[N];

int main()
{
	int tag=0,rank,p,a,b;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(w,&rank);
	MPI_Comm_size(w,&p);
	if(rank == 0)
		printf("%i\n",p);

	if(rank == 0)
	{
		for(int i=0;i<p;i++)
			scanf("%i",&arr[i]);
	}
	MPI_Scatter(arr,1,MPI_INT,&a,1,MPI_INT,0,w);
	for(int i=1;i<p;i*=2)
	{
		if(rank+i < p)
			MPI_Send(&a,1,MPI_INT,rank+i,tag,w);	//send to rank+2^ith node
		if(rank-i >= 0)
		{
			MPI_Recv(&b,1,MPI_INT,rank-i,tag,w,&status);	//recieve from rank-2^ith node
			a += b;
		}

	}
	printf("%i has %i\n",rank,a);

	MPI_Finalize();

	return 0;
}