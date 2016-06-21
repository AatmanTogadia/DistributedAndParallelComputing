#include "HW6_header.h"

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

	
		
	FILE* fp = fopen("inputMatrix1.txt", "r");
	FILE* fp2 = fopen("inputMatrix2.txt", "r");	
		

	int a,b;
	char *read_line=NULL;
	int i=0,j=0;
	int x=0,y=0,z=0;
	size_t count=0;
	double sum = 0;
	int p=0,q=0;
	char *token,line[10000000];
	char *token2,line2[10000000];
	char comma[2];
	int k=0 ,i1=0,p1=0;

	
	if(fp == NULL){
		printf("Error in file reading\n");
	}
	else{
		

		for (i=0;getline(&read_line, &count, fp)!= -1;i++) 
		{
			
			sprintf(line, "%s", read_line);
			if(i == 0)
			{
				size = atoi(read_line);
				
				matrixElements1 = malloc(size * sizeof(float));
				for(i1=0;i1<size;i1++)
				{
					matrixElements1[i1] = (uintptr_t)malloc(size * sizeof(float)); 
				}
			}
			else 
			{
				token = strtok(line, ",");
				j = 0;
				matrixElements1[(i-1)*size + (j)] = 0;
				while( token != NULL ) 
				{
					
					matrixElements1[(i-1)*size+j] = atof(token);
					
					j++;
					token = strtok(NULL, ",");
				}
			}
		}
		
		
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
				
				matrixElements2 = malloc(size2 * sizeof(float));
				for(p1=0;p1<size2;p1++)
				{
					matrixElements2[p1] = (uintptr_t)malloc(size2* sizeof(float));
				}
			}
			else
			{
				
				token2 = strtok(line2,",");
				q = 0;
				while( token2 != NULL ) 
				{
					
					matrixElements2[(p-1)*size2 + q] = atof(token2);
					
					q++;
					token2 = strtok(NULL, ",");
				}
			}
		}
	}
	
	//output matrix  
	resultMatrix = malloc(size*sizeof(float));
	for(i=0;i<size;i++)
	{
		resultMatrix[i] = (uintptr_t)malloc(size*sizeof(float));
	}


	// matrix multiplication	  
		
	for (x = 0; x < size; x++)
	{
	for (y = 0; y < size; y++) 
	{
	resultMatrix[x*size+y]=0;
	for ( z = 0; z < size; z++)
	{
	
	resultMatrix[(x*size)+y] += matrixElements1[(x*size)+z] * matrixElements2[(z*size)+y];
	}

	}
	} 	

	FILE* fp3 = fopen("outputMatrixSerial.txt", "w");

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