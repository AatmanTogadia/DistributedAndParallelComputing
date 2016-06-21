#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/time.h>


#define ITERATIONS 1
#define total_threads 1


double *stackElements;
int size,StackCount=0;
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

struct stack {
   double *s; //Creating a structure for stack . 
   int top; //st.top is the top most element in the stack.
} st;

long long GetStackCount()
{
	//printf("\n\nstack count is %d\n",st.top); //Stack count will start from 0 , So for 10 elements,maximum Stack count=9.

	return st.top;
}


void push(double number)
{
	
	//printf("push top size %d\n",st.top); //pushing every element in stack from the file one-by-one.
	if(st.top==size-1)
	//if(st.top==st.s[size-1])
	 {
			st.s[st.top] = number;
			//printf("inserted --- %f\n",st.s[st.top]);
			//printf("\nstack is full\n\n\n\n");
			
		
	 }
	 else
	 {
	st.s[st.top] = number;
	//printf("inserted --- %f\n",st.s[st.top]);
	st.top++;
	
	}
}

void pop() {
	
   	
	//printf("top size %d\n",st.top); //Deleting the last element from the stack one-by-one till the stack gets empty.
	if(st.top == 0)
	   {
		 
		// printf("deleted %f\n",st.s[st.top]);   
        // printf("\nstack empty\n");
		//st.top--;
	   }
   else
   {
	
   
   //printf("deleted %f\n",st.s[st.top]);
   st.top--;
   //printf("top size %d\n",st.top);
    
   
	}

}




void main()
{
start();
	
FILE* fp = fopen("numbers.txt", "r");	
st.top=0;
int number=5;

char * read_line;
int i,j=0;

int x=0,y=0,z=0;
size_t count=0;
int p=0,q=0;
char * token=0,line[1000000];
char comma[2];
int k=0 ,i1=0,p1=0;

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
	  //printf("SIZE %d\n",size);
	  stackElements = malloc(size * sizeof(double));
	  for(i1=0;i1<size;i1++)
	  {
		  stackElements[i1] = (uintptr_t)malloc(size * sizeof(double)); //taking dynamic array size
	  }
	}
  else 
	   
   {
      token = strtok(line, ",");
      j = 0;
	  stackElements[(i-1)*size + (j)] = 0;
      while( token != NULL ) 
      {
		  //printf("%s\n",token);
		stackElements[(i-1)*size + (j)] = atof(token);
		//printf("Print---%f-%d:%d \n",stackElements[(i-1)*size + (j)],(i-1),j);
        j++;
        token = strtok(NULL, ",");
	  }
    }
  }
  
st.s = malloc(size * sizeof(double));
	  for(i1=0;i1<size;i1++)
	  {
		  st.s[i1] = (uintptr_t)malloc(size * sizeof(double)); //creating stack using dynamic array
		  
	  }  

for(q=0;q<total_threads;q++)
{
for(j=0;j<ITERATIONS;j++)
{	
	 
	for(i=0;i<size;i++)
	{
	
		push(stackElements[i]);
	
		GetStackCount();
	
	}
		for(k=size-1;k>=0;k--)
		{

		pop();
		GetStackCount();

		}

}

}
	 stop();
}































