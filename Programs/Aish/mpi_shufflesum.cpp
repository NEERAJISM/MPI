#include<mpi.h>
#include<stdio.h>

#define N 50

int arr[N];

int shuffle(int x,int p)
{
	x <<= 1;
	if(x >= p)
	{
		x -= p;
		x += 1;
	}
	return x;
}

int rev_shuffle(int x,int p)
{
	if(x&1)
		x += p;
	x >>= 1;
	return x;
}

int main()
{
	int tag=0,rank,p,a,b;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(w,&p);
	MPI_Comm_rank(w,&rank);

	if(rank == 0)
	{
		printf("Enter the elelments\n");
		for(int i=0;i<p;i++)
			scanf("%i",&arr[i]);
	}
	MPI_Scatter(arr,1,MPI_INT,&a,1,MPI_INT,0,w);

	for(int i=1;i<p;i*=2)
	{

		if(shuffle(rank,p) != rank)
		{
			MPI_Send(&a,1,MPI_INT,shuffle(rank,p),tag,w);
			MPI_Recv(&a,1,MPI_INT,rev_shuffle(rank,p),tag,w,&status);
		}
		//exchage step

		MPI_Send(&a,1,MPI_INT,rank^1,tag,w);
		MPI_Recv(&b,1,MPI_INT,rank^1,tag,w,&status);
		a += b;
	}
	if(rank == p-1)
	printf("sum is %i",a);
	MPI_Finalize();

	return 0;
}