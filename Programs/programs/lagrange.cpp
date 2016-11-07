#include <bits/stdc++.h>
#include "mpi.h"

int main()
{
	int rank,p,tag=0;
	MPI_Init(NULL,NULL);
	MPI_Comm c = MPI_COMM_WORLD;
	MPI_Comm_rank(c,&rank);
	MPI_Comm_size(c,&p);
	float arr[10],ans[5];
	if(rank == 0)
	{
		printf("Enter the x's and y's\n");
		for(int i=0;i<10;i++)
			scanf("%f",&arr[i]);
	}

	{
		float temp=1;
		MPI_Bcast(arr,10,MPI_FLOAT,0,c);
		for(int i=0;i<10;i+=2)
		{
			if(2*rank != i)
			{
				temp *= (0.3 - arr[i])/(arr[2*rank] - arr[i]);
			}
		}
		temp *= arr[2*rank+1];
		MPI_Gather(&temp,1,MPI_FLOAT,ans,1,MPI_FLOAT,0,c);
	}

	if(rank == 0)
	{
		float value=0;
		for(int i=0;i<5l;i++)
			value+= ans[i];
		printf("The interpolation value is : %f\n",value); 
	}
		
	MPI_Finalize();
	return 0;
}

