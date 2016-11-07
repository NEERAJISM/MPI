#include<stdio.h>
#include<mpi.h>

int computeSum(int a[],int my_rank)
{
	int sum=0;
	int i;
	for(i=0;i<=my_rank;i++)
	{
		sum=sum+a[i];
	}
	return sum;
}
int main(int argc, char** argv)
{
	int my_rank;
	int p;
	int a[5]={0,1,2,3,4};
	int pSum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);	
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	pSum=computeSum(a,my_rank);
	printf("Rank = %d, sum = %d\n ",my_rank,pSum);
	MPI_Finalize();
}	
