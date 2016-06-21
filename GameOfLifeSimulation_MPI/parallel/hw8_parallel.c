#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<stdint.h>
#include<sys/time.h>
#include"mpi.h"


int *matrix;

int *temp;
int row,col,loops;

struct timeval tm1, tm2; 

 
void start()
{
	gettimeofday(&tm1, NULL);
}


void stop(){
	gettimeofday(&tm2, NULL);
	unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000)
	+ (tm2.tv_usec - tm1.tv_usec);
	printf("\nExecution Time : %llu microseconds\n",t);
}

void main(int argc , char *argv[])
{



	
	int a,b,k;
	int row,col,loops;
	row = atoi(argv[1]);
	col = atoi(argv[2]);
	loops = atoi(argv[3]);
	
	row=row+2;
	col=col+2;

	int  rank,CommSize, source, destination, tag=0,i;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &CommSize);
	MPI_Status stats;
	
	matrix = (int *)malloc( (row+2) * (col+2) * sizeof(int));
	
	
	temp = (int *)malloc( (row+2) * (col+2) * sizeof(int)); 
	
	
	for(a=0;a<row;a++)
	
	{
		
		
		for(b=0;b<col;b++)
		{			
			
			temp[a*row+b] = 3;
			
		}
	}	
	
	
	int count=0;
	
	if(rank==0)
	{
	start();
	}
	if(rank==0)
	{
		
		for(a=0;a<row;a++)
		
		{
			
			
			for(b=0;b<col;b++)
			{
				
				
				matrix[a*row+b] = 0;
				
				
				
			}
			
			
		}
		

		
		for(a=1;a<row-1;a++)
		
		{
			
			const random=rand()%2;
			for(b=1;b<col-1;b++)
			{
				
				
				matrix[a*row+b] = random;
				
			}
			
			
		}
	}
	
	
	if(rank==0)
	{
		printf("Start: %d\n\n",rank);
		for(a=1;a<row-1;a++)
		
		{
			for(b=1;b<col-1;b++)
			{
				printf("%d ",matrix[a*row+b]); 
			}
			printf("\n");
		}
	}
	MPI_Bcast(matrix,row*col,MPI_INT,0,MPI_COMM_WORLD);
	
	
	int x,y;
	int lines = row/CommSize;
	int start = rank*lines;
	int stop = start+lines-1;
	
	int n,m;
	int e,f;
	
	
	
	
	
	for(k=0;k<loops;k++)
	{
		
		
		for(e=0;e<row;e++)
	
	{
		
		
		for(f=0;f<col;f++)
		{			
			
			temp[e*row+f] = 3;
			
		}
	}	
		MPI_Bcast(matrix,row*col,MPI_INT,0,MPI_COMM_WORLD);
		if(rank==0)
		{	
			printf("Round %d\n",k);
		}
		MPI_Barrier(MPI_COMM_WORLD);
		for(a=start+1;a<=stop+1;a++)
		
		{
			for(b=1;b<col-1;b++)
			{	
				
				if(matrix[a*row+b] == 1)
				{
					n=0;
					
					if(matrix[((a-1)*row)+(b-1)] == 1)   
					n++;
					if(matrix[((a-1)*row)+b] == 1)		
					n++;
					if(matrix[((a-1)*row)+(b+1)] == 1)	
					n++;
					if(matrix[a*row+(b-1)] == 1)
					n++;
					if(matrix[a*row+(b+1)] == 1)		
					n++;
					if(matrix[((a+1)*row)+(b-1)] == 1)	
					n++;
					if(matrix[((a+1)*row)+b] == 1)		
					n++;
					if(matrix[((a+1)*row)+(b+1)] == 1)	
					n++;
					if(n==1 || n==0 || n>=4) 
					
					{
						
						temp[a*row+b] = 0;
						
					}
				}
				else 
				{
					m=0;
					if(matrix[((a-1)*row)+(b-1)] == 1)   
					m++;
					if(matrix[((a-1)*row)+b] == 1)		
					m++;
					if(matrix[((a-1)*row)+(b+1)] == 1)	
					m++;
					if(matrix[a*row+(b-1)] == 1)
					m++;
					if(matrix[a*row+(b+1)] == 1)		
					m++;
					if(matrix[((a+1)*row)+(b-1)] == 1)	
					m++;
					if(matrix[((a+1)*row)+b] == 1)		
					m++;
					if(matrix[((a+1)*row)+(b+1)] == 1)	
					m++;
					if(m==1 || m==0 || m>=4) 
					
					{
						
						temp[a*row+b] = 0;
						
					}
					
					
					
				}
				
				
				
				
				
				
				
				
				
			}
			
			
		}
		
		int j,temp1;		
		
		MPI_Barrier(MPI_COMM_WORLD);

		for(i = start+1; i <=stop+1; i = i+1)
		{
			MPI_Send(&temp[i*row+0],col, MPI_INT, 0,0, MPI_COMM_WORLD);	
		}
		
		
		
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == 0)
		{
			
			for(i = 0; i < CommSize; i++)
			{
				int temp1 = lines;
				
				for( j=(i*lines)+1;temp1>0; j++)
				{
					
					MPI_Recv(&matrix[j*row+0], col, MPI_INT,i ,0, MPI_COMM_WORLD, &stats);	
					temp1--;
					
				}
			}
		}		
		
		MPI_Barrier(MPI_COMM_WORLD);
		int p,q;	
		if(rank==0)
		{
			
			for(a=1;a<row-1;a++)
			
			{
				for(b=1; b<col-1;b++)
				{
					if(matrix[a*row+b]==3)
					{
						matrix[a*row+b]=1;
					}
					printf("%d ",matrix[a*row+b]); 
				}
				printf("\n");
			}
			
		}
		
		
		
	}	
	if(rank==0)
		{
	gettimeofday(&tm2, NULL);
	unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000)
	+ (tm2.tv_usec - tm1.tv_usec);
	printf("\nExecution Time : %llu microseconds\n",t);
		}	
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	
	
	MPI_Finalize();
	
	
	

	
}