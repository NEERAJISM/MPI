#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#define sf scanf
#define pf printf
int main(int argc,char* argv[]){
	int me,p,src,dest=0,tag=0;
	int i,j,n,m;
	float x[1000010],row[1010],y[1010],ans[1010],val,res;
	
	MPI_Init(&argc,&argv);
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Status stat;
	MPI_Comm_size(comm,&p);
	MPI_Comm_rank(comm,&me);
	
	if(me==0){
		sf("%d %d",&n,&m);
		for(i=0;i<m*n;i++){
				sf("%f",&x[i]);
			}
		for(i=0;i<m;i++)
			sf("%f",&y[i]);
	}
	
	MPI_Bcast(&n,1,MPI_INT,0,comm);
	MPI_Bcast(&m,1,MPI_INT,0,comm);
	MPI_Bcast(y,m,MPI_FLOAT,0,comm);
	MPI_Scatter(x,m,MPI_FLOAT,row,m,MPI_FLOAT,0,comm);
	
	val=0;
	for(i=0;i<m;i++)
		val+=row[i]*y[i];
	
	MPI_Gather(&val,1,MPI_FLOAT,ans,1,MPI_FLOAT,0,comm);
	
	if(me==0){
		for(i=0;i<m;i++)
			pf("%f ",ans[i]);
	}
	
	MPI_Finalize();
	return 0;
}
