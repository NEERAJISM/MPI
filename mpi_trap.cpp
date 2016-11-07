#include <bits/stdc++.h>
#include <mpi.h>

// THE FUCTION HERE IS X^2
float f(float x)
{
	return x*x;
}

float trap(float local_a,float local_b,int local_n,float h)
{
	float integral,x,i;

	integral = (f(local_a)+f(local_b))/2.0;
	x=local_a;
	for(i=1;i<=local_n-1;i++)
	{	
		x=x+h;
		integral=integral+f(x);
	}
	integral=integral*h;
	return integral;
}

int main(int argc, char** argv)
{
	int my_rank,p , n = 1024 , local_n, source, dest = 0, tag = 0;
	float a=0.0,b=1.0 ,h , local_a, local_b,integral,total;
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	
	h=(b-a)/n;
	local_n=n/p;
	local_a=a+my_rank*local_n*h;
	local_b=local_a+local_n*h;
	integral=trap(local_a,local_b,local_n,h);
	
	if(my_rank==0)
	{
		total=integral;
		for(source=1;source<p;source++)
		{
			MPI_Recv(&integral,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
			total+=integral;
		}
	}
	else
	{
		MPI_Send(&integral,1,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
	}


	if(my_rank==0)
	{
		printf("With n= %d trapezoids intergral is %f\n",n,total);
	}
	MPI_Finalize();
}
