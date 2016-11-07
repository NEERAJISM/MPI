#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#define REP(i,a,b) for(i=a;i<=b;i++)
#define sf scanf
#define pf printf
int main(int argc,char* argv[]){
	int me,p,src,dest=0,tag=0;
	int i,n;
	float xx,x[1010],y[1010],ans[1010],val,res;
	
	MPI_Init(&argc,&argv);
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Status stat;
	MPI_Comm_size(comm,&p);
	MPI_Comm_rank(comm,&me);
	
	if(me==0){
		sf("%d %f",&n,&xx);
		val=1;
		for(i=0;i<n;i++){
			sf("%f",&x[i]);
			val*=(xx-x[i]);
		}
		for(i=0;i<n;i++)
			sf("%f",&y[i]);
	}
	
	MPI_Bcast(&n,1,MPI_INT,0,comm);
	MPI_Bcast(&xx,1,MPI_FLOAT,0,comm);
	MPI_Bcast(x,n,MPI_FLOAT,0,comm);
	MPI_Bcast(y,n,MPI_FLOAT,0,comm);
	MPI_Bcast(&val,1,MPI_FLOAT,0,comm);
	
	if(me>0){
		val/=(xx-x[me-1]);
		for(i=0;i<n;i++)
			if(i!=me-1)
				val/=(x[me-1]-x[i]);
		val*=y[me-1];
		//pf("%f\n",val);
	}
	
	MPI_Gather(&val,1,MPI_FLOAT,ans,1,MPI_FLOAT,0,comm);
	
	if(me==0){
		res=0;
		for(i=1;i<=n;i++)
			res+=ans[i];
		pf("%f\n",res);
	}
	
	MPI_Finalize();
	return 0;
}
