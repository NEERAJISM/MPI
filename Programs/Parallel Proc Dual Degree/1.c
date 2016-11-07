#include<stdio.h>
#include<string.h>
#include "mpi.h"
int main(int argc,char* argv){
	int rnk,src,dest=0,tag=0,p;
	char mesg[100010];
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rnk);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	if(rnk!=0){
		sprintf(mesg,"blah blah.. %d",rnk);
		MPI_Send(mesg,strlen(mesg)+1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
	}else{
		for(src=1;src<p;src++){
			MPI_Recv(mesg,100,MPI_CHAR,src,tag,MPI_COMM_WORLD,&stat);
			printf("%s\n",mesg);
		}
	}
	MPI_Finalize();
}
