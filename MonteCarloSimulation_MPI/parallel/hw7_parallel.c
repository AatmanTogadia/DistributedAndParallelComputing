#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/time.h>
#include"mpi.h"


struct timeval tm1, tm2;

void start()
{
	gettimeofday(&tm1, NULL);
}

void stop()
{
	gettimeofday(&tm2, NULL);
	unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000)
	+ (tm2.tv_usec - tm1.tv_usec);
	printf("\n%llu microseconds occured\n",t);
}

double getRand(double min, double max)
{
	double d = (double)rand() / RAND_MAX;
	return min + d * (max - min);
}


void main(int argc, char* argv[])
{

	start();

	double min=0.00001, max=1.0;
	int i=0; 
	double iterations;

	double x,y,z;
	int count=0;	
	int rank, CommSize, source, destination, tag=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &CommSize);
	MPI_Status stats;
	
	
	
	double pi;
	int j;
	iterations = atof(argv[1]);
	

	if(rank==0)
	{
		start();
	}
	float temp;
	
	
	int lines = iterations/CommSize;
	int start = rank*lines;
	int stop = start+lines-1;
	// printf("rank %d start : %d stop : %d\n",rank,start,stop);
	
	
	for ( i=start; i<=stop; i++)  
	{
		
		x = getRand(min,max);
		
		
		y = getRand(min,max);
		
		z = x*x+y*y;
		
		if (z<=1) 
		{
			count++;
		}
	}  

	int recBuf=0;



	MPI_Reduce(&count,&recBuf,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);


	
	MPI_Barrier(MPI_COMM_WORLD); 	
	
	
	if(rank==0)
	{
		
		pi=(double)recBuf/iterations*4;
		printf("pi is %g \n",pi);
		gettimeofday(&tm2, NULL);
		unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000)
		+ (tm2.tv_usec - tm1.tv_usec);
		printf("\n%llu microseconds occured\n",t);
		
	}
	
	
	
	MPI_Finalize();
	
}




