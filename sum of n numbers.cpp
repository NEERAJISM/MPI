#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
int main(int argc, char ** argv)
{
	int myrank,res,p,dst = 0,tag = 0,ar[100],i;

	for(int i=0;i<100;i++)
		ar[i] = i;
	
	MPI_Status status;
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(myrank != 0)
	{
		int interval = 100/(p-1),x,y;
		x = interval*(myrank-1);
		y = interval*(myrank)-1;

		res = 0;
		for(i=x;i<=y;i++)
			res+=ar[i];
		// cout<<"sum "<<res <<"\n";
		MPI_Send(&res, sizeof(res), MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else
	{
		int sum = 0;
		for(int src= 1; src< p; src++)
		{
			MPI_Recv(&res, sizeof(res), MPI_INT, src, 0, MPI_COMM_WORLD, &status);
			printf("sum recieved from the process: %d is %d\n",src, res);
			sum = sum + res;
		}
	 	printf("the total sum is %d\n",sum);
	 }
	 
	MPI_Finalize();
}	