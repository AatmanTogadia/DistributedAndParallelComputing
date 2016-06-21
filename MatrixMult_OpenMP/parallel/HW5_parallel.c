/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/time.h>

#include<omp.h>*/
#define numThreads 20
#include "HW5_header.h"

struct timeval tm1, tm2;

//double *matrixElements1,*matrixElements2 , *resultMatrix;
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

void main()
{
	start();

	// printf("adasd");
		
	FILE* fp = fopen("inputMatrix1.txt", "r");
	FILE* fp2 = fopen("inputMatrix2.txt", "r");	
		

	int a,b;
	//int size=0 , size2 =0;
	char *read_line=NULL;
	int i=0,j=0;
	int x=0,y=0,z=0;
	size_t count=0;
	double sum = 0;
	int p=0,q=0;
	char *token,line[1000000];
	char *token2,line2[1000000];
	char comma[2];
	int k=0 ,i1=0,p1=0;

	// //first matrix
	if(fp == NULL){
		printf("Error in file reading\n");
	}
	else{
		//printf("sadasd");

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
		
		// printf("Stored in Array 1\n");
		// for(i=0;i<size;i++){
		// for(j=0;j<size;j++){
		// printf("%f\n",matrixElements1[i*size+j]);
		// }
		// }
		// fclose(fp);
	}
	

	//second matrix
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
	// for(i=0;i<size;i++){
		// for(j=0;j<size;j++){
			// printf("%f \n",matrixElements2[i*size+j]);
		// }
	// }


	// fclose(fp2);

	//output matrix  
	resultMatrix = malloc(size*sizeof(float));
	for(i=0;i<size;i++)
	{
		resultMatrix[i] = (uintptr_t)malloc(size*sizeof(float));
	}


	// matrix multiplication	  
		
	#pragma omp parallel num_threads(numThreads) firstprivate(x,y,z) shared(resultMatrix,matrixElements1,matrixElements2) 
	{
	#pragma omp for schedule(dynamic,numThreads) ordered
	for (x = 0; x < size; x++)
	{
	for (y = 0; y < size; y++) 
	{
	resultMatrix[x*size+y]=0;
	for ( z = 0; z < size; z++)
	{
	// #pragma omp atomic
	resultMatrix[(x*size)+y] += matrixElements1[(x*size)+z] * matrixElements2[(z*size)+y];
	}
	//printf("\n%f",resultMatrix[x*size+(y)] );
	}
	} 

	}
	 //}
		
//	printf("threads --- %d",numThreads);
//	printf("size ---%d",size);	
	

	FILE* fp3 = fopen("outputMatrixParallel.txt", "w");

	fprintf(fp3, "%d\n", size);
	for(a=0;a<size;a++)
	{
	sprintf(comma, "%s", "");

	for(b=0;b<size;b++)
	{
	fprintf(fp3, "%s%f",comma,resultMatrix[a*size+b]);
	sprintf(comma, "%s", ",");;
	}
	fprintf(fp3, "\n");
	}

	// // fclose(fp3); 
	stop();
	

}