#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

float f(float x)
{
	return (x*x);
}

float trap(float n , float x1, float x2, float h)
{
	float res  = (f(x1) + f(x2))/2.0,x = x1;

	for(int i=1; i< n;i++)
	{
		x+=h;
		res+=f(x);
	}
	res*=h;
	return res;
}


int main(int argc, char** argv)
{
	int p,i, myrank;
	float x1 = 1 ,x2 = 50, n = 50 , local_n, local_x1 , local_x2 , h , integral;
	float *res;

	h = (x2-x1)/n;
	local_n = n/p;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	local_x1 = x1 + myrank*(h)*local_n;
	local_x2 = local_x1 + h*local_n;

	integral = trap(local_n,local_x1,local_x2,h);

	if(myrank == 0)
	{
		res = (float*) malloc(sizeof(float)*p);
	}

	MPI_Gather(&integral,1,MPI_FLOAT,res,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(myrank == 0)
	{
		for(i=0;i<p;i++)
			cout<<res[i]<<" ";
	}

	MPI_Finalize();
	return 0;
}