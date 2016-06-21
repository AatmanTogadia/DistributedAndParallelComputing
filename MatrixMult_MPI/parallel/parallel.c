#include "HW6_header.h"
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
void main(int argc , char **argv)
{
	
	int rank, CommSize, source, destination, tag=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &CommSize);
	MPI_Status stats;
	
	
	
	

	int a,b;
	//int size=0 , size2 =0;
	char *read_line=NULL;
	int i=0,j=0;
	int x=0,y=0,z=0;
	size_t count=0;
	double sum = 0;
	int p=0,q=0;
	char *token,line[100000];
	char *token2,line2[100000];
	char comma[2];
	int k=0 ,i1=0,p1=0;
	

	
	// //first matrix
	
	FILE* fp = fopen("inputMatrix1.txt", "r");
	
	if(fp == NULL){
		printf("Error in file reading\n");
	}
	else{
		

		for (i=0;getline(&read_line, &count, fp)!= -1;i++) 
		{
			// printf("i--%d\n",i);
			sprintf(line, "%s", read_line);
			if(i == 0)
			{
				size = atoi(read_line);
				// printf("SIZE %d\n",size);
				matrixElements1 = malloc(size * sizeof(float));
				for(i1=0;i1<size;i1++)
				{
					matrixElements1[i1] = (uintptr_t)malloc(size * sizeof(float)); //taking dynamic array size
				}
			}
			else 
			{
				token = strtok(line, ",");
				j = 0;
				matrixElements1[(i-1)*size + (j)] = 0;
				while( token != NULL ) 
				{
					// printf("%s\n",token);
					//printf("%d|%d\n",i-1,j);
					matrixElements1[(i-1)*size+j] = atof(token);
					// printf("Print---%f-%d:%d \n",matrixflements1[(i-1)*size + (j)],(i-1),j);
					j++;
					token = strtok(NULL, ",");
				}
			}
		}
		
	}
	fclose(fp);
	
	// //second matrix
	FILE* fp2 = fopen("inputMatrix2.txt", "r");	
	if(fp2 == NULL){
		printf("Error in file reading\n");
	}
	else{
		for (p=0;getline(&read_line, &count, fp2)!= -1;p++) 
		{
			sprintf(line2, "%s", read_line);
			if(p == 0)
			{
				size2 = atoi(read_line);
				//printf("SIZE2--%d\n",size2);
				matrixElements2 = malloc(size2 * sizeof(float));
				for(p1=0;p1<size2;p1++)
				{
					matrixElements2[p1] = (uintptr_t)malloc(size2* sizeof(float));
				}
			}
			else
			{
				// printf("%s",line2);
				token2 = strtok(line2,",");
				q = 0;
				while( token2 != NULL ) 
				{
					//printf("%s -:%d : %d \n ",token2,p-1,q);
					//printf("%d|%d\n",p-1,q);
					matrixElements2[(p-1)*size2 + q] = atof(token2);
					//printf("%f\n",matrixElements2[(p-1)*size + (q)]);
					q++;
					token2 = strtok(NULL, ",");
				}
			}
		}
	}
	fclose(fp2);
	
	
	
	resultMatrix = malloc(size*sizeof(float));
	for(i=0;i<size;i++)
	{
		resultMatrix[i] = (uintptr_t)malloc(size*sizeof(float));
	}
	
	
	

	if(rank==0)
	{
	start();
	}
	float temp;
	// //printf("id is %d\n",t);
	
	int lines = size/CommSize;
	int start = rank*lines;
	int stop = start+lines-1;
	// printf("rank %d start : %d stop : %d\n",rank,start,stop);
	
		
for(i = start; i <= stop; i=i+1) 
	{
		for(j = 0; j < size; j++)
		{
			temp=0;
			resultMatrix[i*size+j]=0;
			for(k = 0; k < size; k++)
			{
				temp += matrixElements1[(i*size)+k] * matrixElements2[(k*size)+j];
			}
			
		
		resultMatrix[i*size+j]=temp;
		
		}
	}	
				
if(rank != 0)
	{
		for(i = start; i <=stop; i = i+1){
		
		MPI_Send(&resultMatrix[i*size+0],size, MPI_INT, 0,CommSize+i, MPI_COMM_WORLD);
		}
	
	}
	
	if(rank == 0)
	{
		
		for(i = 1; i < CommSize; i++)
		{
			int temp = lines;
		
			for( j=i*lines;temp>0; j++)
			{
			
			MPI_Recv(&resultMatrix[j*size+0], size, MPI_INT,i ,CommSize+j, MPI_COMM_WORLD, &stats);
			temp--;
			
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD); 
	
	 
	
	if(rank==0)
	{
	gettimeofday(&tm2, NULL);
	unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000)
	+ (tm2.tv_usec - tm1.tv_usec);
	printf("\n%llu microseconds occured\n",t);
	}
	
	if(rank==0){
		
	FILE* fp3 = fopen("outputMatrixPrallel.txt", "w");
	
	fprintf(fp3, "%d\n", size);
	for(a=0;a<size;a++)
	{
		sprintf(comma, "%s", "");
		for(b=0;b<size;b++)
		{
			//printf("%f-%d:%d\n",resultMatrix[a*size+b],a,b);
			fprintf(fp3, "%s%f",comma,resultMatrix[a*size+b]);
			sprintf(comma, "%s", ",");;
		}
		fprintf(fp3, "\n");

		
	}		
	fclose(fp3); 
	}

	
	
		
	MPI_Barrier(MPI_COMM_WORLD);
	
	
	
	MPI_Finalize();
	
}
