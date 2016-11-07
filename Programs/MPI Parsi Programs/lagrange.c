#include<stdio.h>
#include<mpi.h>

float computeL(int x,int a[],int my_rank,int n)
{
	int numerator=1;
	int i;
	int denominator=1;
	for(i=0;i<n;i++)
	{
		if(i!=my_rank)
		{
			numerator=numerator*(x-a[i]);
			denominator=denominator*(a[my_rank]-a[i]);
		}
	}
	float ans=numerator/denominator;
	return ans;
}
int main(int argc, char** argv)
{
	int my_rank;
	int a[5]={0,1,2,3,4};
	int b[5]={0,1,2,3,4};
	int source;
	int p;
	int x=5;
	int dest=0;
	int tag=0;
	MPI_Status status;
	float total;
	float local;
	float term;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	local=computeL(x,a,my_rank,5);
	term=local*b[my_rank];
	if(my_rank==0)
	{
		total=term;
		for(source=1;source<p;source++)
		{
			MPI_Recv(&term,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
			total=total+term;
		}
	}
	else
	{
		MPI_Send(&term,1,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
	}
	if(my_rank==0)
	{
		printf("%f is the estimate", total);
	}
	MPI_Finalize();
}
	
	
