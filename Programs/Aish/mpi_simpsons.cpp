#include<mpi.h>
#include<stdio.h>

double func(double x) //evaluate the function
{
	return x*x;
}

int main()
{
	double x,ini = 1,fin = 8;
	int tag=0,rank,p;
	MPI_Status status;
	MPI_Comm w = MPI_COMM_WORLD;
	double partial=0;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(w,&rank);
	MPI_Comm_size(w,&p);

	x = ini + (fin - ini)/(p-1) * rank;
	if(rank == 0 || rank == p-1)
	{
		partial = func(x); // calulate corresponding x value and evaluate
	}
	else if(rank%2 == 0)
	{
		partial = 2*func(x); // calulate corresponding x value and evaluate
	}
	else
	{
		partial = 4 * func(x);
	}
	printf("process %i partial sum %lf\n",rank,partial);
	if(rank != 0)
	{
		MPI_Send(&partial,1,MPI_DOUBLE,0,tag,w);
	}
	else
	{
		int i;
		double temp;
		for(i=1;i<p;i++)
		{
			MPI_Recv(&temp,1,MPI_DOUBLE,i,tag,w,&status);
			partial += temp;
		}
		temp = (fin - ini)*partial/(p-1);
		printf("the integral evaluation is %lf\n",temp/3);
	}
	MPI_Finalize();
	return 0;
}