#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	float x[5] = {0.0,1.0,3.0,4.0};
	float f[5] = {1.0,3.0,49.0,129.0};
	float x = 0.3, res = 0,pass[4],recv[2];
	int my_rank,p;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// Scatter the random numbers to all processes
	MPI_Scatter(x, 2, MPI_FLOAT, pass, 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	float l = 0,num = 1.0,den = 1.0,mul;

	for(j=0;j<2;j++)
	{
		float x0 = pass[0],num = 1.0,den = 1.0;
		for(i=0;i<3;i++)
		{
			if(i == j)
				continue;
			
			num *= (0.3-pass[i]);
			den *= (x0 - pass[i]);
		}

		res += ((num/den)*f[j]);		
	}

	//gather
	MPI_Gather(&res, 1, MPI_FLOAT, recv, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);

	if (world_rank == 0) {
		cout<<"The value of the function at 0.3 is : "<<recv[0]+recv[1];	
	}

MPI_Finalize();
return 0;
}
