#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int i,myrank,res,p,src,dst,tag = 0,ar[100];
	char message[100];

	for(i=0;i<100;i++)
		ar[i] = i;
	
	MPI_Status status;
	MPI_Init (&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	dst = 0;
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if(myrank != 0)
	{
		//sprintf(message, "");
		int interval = 100/(p-1),x,y;
		
		x = interval*(myrank-1);
		y = interval*(myrank)-1;

		if(y > 99)
			y  = 99;

		res = 0;
		for(i=x;i<=y;i++)
			res+=ar[i];

		MPI_Send(&res, sizeof(res), MPI_INT, dst, tag, MPI_COMM_WORLD);
	}
	else
	{
		int sum = 0;
		for(src = 1; src < p;src++)
		{
			MPI_Recv(&res, 4, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
			printf("sum recieved from the process: %d is %d\n",src, res);
			sum+=res;
		}
		printf("the total sum is %d\n",sum);
	}
	MPI_Finalize();
}