#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;
int main(int argc, char** argv)
{
	int i,j,k,p,a[100],myrank,res,x,y,interval,sum = 0;

	for(i=0;i<100;i++)
		a[i] = i;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(myrank!=0)
	{
		interval = 100/(p-1);
		x = (myrank-1)*interval;
		y = x + (interval - 1);
	
		res = 0;
		for(j=x;j<=y;j++)
			res+=a[j];
		printf("%d\n",res );
		MPI_Send(&res,1, MPI_INT,0,0,MPI_COMM_WORLD);
	}
	else
	{
		for(k = 1;k<p;k++)
		{
			MPI_Recv(&res, 1, MPI_INT,k,0,MPI_COMM_WORLD, &status);
			sum = sum + res;
		}

		printf("sum = %d\n",sum);
	}

	MPI_Finalize();
	return 0;
}