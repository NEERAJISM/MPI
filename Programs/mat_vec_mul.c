#include<stdio.h>
#include "mpi.h"
int main(int argc,char *argv[])
{
	
	int my_rank;
	int p;
	int destination=0;
	int m[10][10],v[10],n,i,j;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	if(my_rank==0)
	{
		scanf("%d",&n);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				scanf("%d",&m[i][j]);
				printf("%d ",m[i][j]);
			}

		for(i=0;i<n;i++)
		{
			scanf("%d",&v[i]);
		}
	}
	MPI_Bcast(&n,1,MPI_INTEGER,0,MPI_COMM_WORLD);
	MPI_Bcast(v,n,MPI_INTEGER,0,MPI_COMM_WORLD);
	
	int localData[10],r[10];

	MPI_Scatter(m,n,MPI_INTEGER,localData,n,MPI_INTEGER,0,MPI_COMM_WORLD);

	int result=0;

	printf("\n\nrank =%d n=%d\n",my_rank,n);
	for(i=0;i<n;i++)
	{
		printf("l=%d v=%d\n",localData[i],v[i]);
	}

	for(i=0;i<n;i++)
	{
		result += localData[i]*v[i];
	}

	printf("rank = %d  result=%d \n",my_rank,result);

	MPI_Gather(&result,1,MPI_INTEGER,r,1,MPI_INTEGER,destination,MPI_COMM_WORLD);

	if(my_rank==0)
	{
		printf("the result is\n");
		for(i=0;i<n;i++)
		{
			printf("i=%d %d\n",i,r[i]);
		}
	}
	
	MPI_Finalize();
}
