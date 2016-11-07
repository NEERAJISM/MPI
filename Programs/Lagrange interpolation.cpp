//Here is the program for Lagrange Interpolation using Broadcast

#include<stdio.h>
#include<string.h>
#include "mpi.h"

int main(int argc,char *argv[])
{
    int my_rank;
    int p,i;
    int source;
    int x[5];
    int y[5];
    int X=3;
    float sum;
    int tag = 0;
    int temp1,temp2;
    float temp;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    if(my_rank==0)
    {
        for(i=0;i<5;i++)
         scanf("%d",&x[i]);
        for(i=0;i<5;i++)
         scanf("%d",&y[i]);
    }
    MPI_Bcast(x,5,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(y,5,MPI_INT,0,MPI_COMM_WORLD);
   temp1=1;
   for(i=0;i<5;i++)
   {
     if(my_rank==i);
     else
       temp1*=(X-x[i]);
   }
   temp2=1;

   for(i=0;i<5;i++)
   {
     if(my_rank==i);
     else
       temp2*=(x[my_rank]-x[i]);
   }
   temp=(float)temp1/(float)temp2;
   temp=temp*(float)y[my_rank];
   MPI_Reduce(&temp,&sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
   if(my_rank == 0)
	printf("%f",sum);
    MPI_Finalize();
    return 0;
}
