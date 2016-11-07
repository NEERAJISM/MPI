#include<stdio.h>
#include<mpi.h>

int computeSum(int a[][3],int x[],int my_rank,int n)
{
	int sum=0;
	int i;
	for(i=0;i<n;i++)
	{
		sum=sum+a[my_rank][i]*x[i];
	}
	return sum;
}
int main(int argc, char** argv)
{
	int my_rank;
	int p;
	int a[3][3]={{0,1,2},{3,4,5},{6,7,8}};
	int x[3]={0,1,2};
	int pSum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);	
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	pSum=computeSum(a,x,my_rank,3);
	printf("c[%d] = %d\n ",my_rank,pSum);
	MPI_Finalize();
}
