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
	int tag=0,rank,p,a,e,x;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(w,&p);
	MPI_Comm_rank(w,&rank);

	if(rank == 0)
	{
		printf("Enter the coefficients\n");
		for(int i=0;i<p-1;i++)
			scanf("%i",&arr[i]);
		printf("Enter x: ");
		scanf("%i",&arr[p-1]);
	}
	MPI_Scatter(arr,1,MPI_INT,&a,1,MPI_INT,0,w);
	if(rank%2 == 0)
		e = 0;
	else
		e = 1;
	if(rank == p-1)
		x = a;
	for(int i=1;i<p;i*=2)
	{

		MPI_Bcast(&x,1,MPI_INT,p-1,w);
		if(e == 1)
			a *=x;
		if(shuffle(rank,p) != rank)
		{
			MPI_Send(&e,1,MPI_INT,shuffle(rank,p),tag,w);
			MPI_Recv(&e,1,MPI_INT,rev_shuffle(rank,p),tag,w,&status);
		}
		x = x*x;

	}
	if(rank != p-1)
	printf("processor %i has %i\n",rank,a);
	MPI_Finalize();

	return 0;
}