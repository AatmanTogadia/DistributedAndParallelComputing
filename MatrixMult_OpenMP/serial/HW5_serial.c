#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/time.h>



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

void main()
{
start();
	
FILE* fp = fopen("inputMatrix1.txt", "r");	
// FILE* fp2 = fopen("inputMatrix1.txt", "r");	
	
int a,b;
int size=0 , size2 =0;
double *matrixElements1,*matrixElements2 , *resultMatrix;

char * read_line , * read_line2;
int i=0,j=0;

int x=0,y=0,z=0;
size_t count=0 ,count2= 0;
int p=0,q=0;
char * token=0,line[1000000];
char * token2=0,line2[1000000];
char comma[2];
int k=0 ,i1=0,p1=0;

//first matrix
if(fp == NULL)
  {
    printf("Error in file reading\n");
  }
  
  for (i=0;getline(&read_line, &count, fp)!= -1;i++) 
  {
	  // printf("i--%d\n",i);
    sprintf(line, "%s", read_line);
    if(i == 0)
    {
      size = atoi(read_line);
	  // printf("SIZE %d\n",size);
	  matrixElements1 = malloc(size * sizeof(double));
	  for(i1=0;i1<size;i1++)
	  {
		  matrixElements1[i1] = (uintptr_t)malloc(size * sizeof(double)); //taking dynamic array size
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
		matrixElements1[(i-1)*size + (j)] = atof(token);
		 // printf("Print---%f-%d:%d \n",matrixElements1[(i-1)*size + (j)],(i-1),j);
        j++;
        token = strtok(NULL, ",");
	  }
    }
  }
		
	
  
 //printf("Stored in Array 1\n");
  fclose(fp);
  
  FILE* fp2 = fopen("inputMatrix2.txt", "r");	
 
 //second matrix
	if(fp2 == NULL)
  {
    printf("Error in file reading\n");
  }
	 for (p=0;getline(&read_line2, &count2, fp2)!= -1;p++) 
  {
    sprintf(line2, "%s", read_line2);
    if(p == 0)
    {
      size2 = atoi(read_line2);
	  //printf("SIZE2--%d\n",size2);
	  matrixElements2 = malloc(size2 * sizeof(double));
	  for(p1=0;p1<size2;p1++)
	  {
		  matrixElements2[p1] = (uintptr_t)malloc(size2* sizeof(double));
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
        matrixElements2[(p-1)*size2 + q] = atof(token2);
		//printf("%f\n",matrixElements2[(p-1)*size + (q)]);
        q++;
        token2 = strtok(NULL, ",");
	  }
    }
  }

  
  fclose(fp2);
  
//output matrix  
  resultMatrix = malloc(size * sizeof(double));
	  for(i=0;i<size;i++)
	  {
	  resultMatrix[i] = (uintptr_t)malloc(size * sizeof(double));
	  }
	  
	
//matrix multiplication	  
	  for (x = 0; x < size; x++)
		{
			for (y = 0; y < size; y++) 
		{
				resultMatrix[x*size+y]=0;
			    for ( z = 0; z < size; z++)
				{
                resultMatrix[(x*size)+(y)] += matrixElements1[(x*size)+(z)] * matrixElements2[(z*size)+(y)];
                }
				//printf("\n%f",resultMatrix[x*size+(y)] );
        }
    } 
	
//printf("size ---%d",size);	
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
	
	// fclose(fp3); 
	// free(matrixElements1);
	// free(matrixElements2);
	
	stop();
  }































