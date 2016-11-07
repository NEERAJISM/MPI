#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include<string.h>
#define f(x) sin(x)
#define sf scanf
#define pf printf
float calc(float a,float b,int n,float h){
	float res,x;
	int i;
	res=(f(a)+f(b))/2.0;
	x=a;
	for(i=1;i<n;i++){
		x+=h;
		res+=f(x);
	}
	return res*h;
}
int main(int argc,char* argv[]){
	int n=100,ln,p,me,src,dst=0,tag=0;
	float a=0,b=1.57,la,lb,h,curr,ans;
	MPI_Comm comm;
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	comm=MPI_COMM_WORLD;
	MPI_Comm_size(comm,&p);
	MPI_Comm_rank(comm,&me);
	h=(b-a)/n;
	ln=n/p;
	la=a+me*ln*h;
	lb=la+ln*h;
	curr=calc(la,lb,ln,h);
	if(me==0){
		ans=curr;
		for(src=1;src<p;src++){
			MPI_Recv(&curr,1,MPI_FLOAT,src,tag,MPI_COMM_WORLD,&stat);
			ans+=curr;
		}
	}else{
		MPI_Send(&curr,1,MPI_FLOAT,dst,tag,MPI_COMM_WORLD);
	}
	if(me==0){
		pf("n=%d\nf(x)=sin(x)\na=%f\tb=%f\nIntegral=%f\n",n,a,b,ans);
	}
	MPI_Finalize();
	return 0;
}
