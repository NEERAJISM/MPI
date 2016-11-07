#include <bits/stdc++.h>
#include "mpi.h"

int main(int argc ,char *argv[])
{
	int my_rank,p,src,dest,tag=0,s=0,x;
	int a[] = {1,2,3,4,5};
	int b[] = {1,2,3,4,5};

	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	dest = 0;
	if(my_rank != 0)
	{
		x = a[my_rank]*b[my_rank];
		MPI_Send(&x,1,MPI_INT,0,tag,MPI_COMM_WORLD);
	}	
	else
	{
		s = a[my_rank]*b[my_rank];
		for(src = 1;src < p;src++)
		{
			MPI_Recv(&x,1,MPI_INT,src,tag,MPI_COMM_WORLD,&status);
			s+=x;
		}
		printf("%d\n",s);
		
	}
	MPI_Finalize();
}
