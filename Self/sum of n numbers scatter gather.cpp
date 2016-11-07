#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;
int main(int argc, char** argv)
{
	int i,j,k,p,a[100],b[25],myrank,res,x,y,interval,sum = 0,c[4];

	for(i=0;i<100;i++)
		a[i] = i;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Scatter(a,25,MPI_INT,b,25,MPI_INT,0,MPI_COMM_WORLD);

	res = 0;
	for(i=0;i<25;i++)
		res+=b[i];


	MPI_Gather(&res,1,MPI_INT, c, 1,MPI_INT,0,MPI_COMM_WORLD);
	
	if(myrank == 0)
	{
		for(i=0;i<4;i++)
			cout<<c[i]<<"\n";
	}

	MPI_Finalize();
	return 0;
}