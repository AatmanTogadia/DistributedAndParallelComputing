#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<stdint.h>
#include<sys/time.h>


int *matrix , *temp;
int row,col,loops;

void alive(int a,int b)
{
	
	int n = 0;
	int count=0;
	
	if(matrix[a*row+b] == 0)
	{
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
		if(n==3 || n==2)
		{
			
			temp[a*row+b] = 1;
		}

	}
	

	
}






void live(int a,int b)
{
	
	int n = 0;
	
	if(matrix[a*row+b] == 1)
	{
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
	
}









void main(int argc , char *argv[])
{



	
	int a,b,k;

	row = atoi(argv[1]);
	col = atoi(argv[2]);
	loops = atoi(argv[3]);
	
	row=row+2;
	col=col+2;

	
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
	
	printf("Start: \n\n");
	for(a=1;a<row-1;a++)
	
	{
		for(b=1;b<col-1;b++)
		{
			printf("%d ",matrix[a*row+b]); 
		}
		printf("\n");
	}

	int x,y,p,q;
	
	for(k=1;k<=loops;k++)
	{
		printf("Round %d\n\n",k);
		for(x=1;x<row-1;x++)
		
		{
			for(y=1;y<col-1;y++)
			{
				alive(x,y);
				live(x,y);
			}
			
			
		}
		
		for(p=1;p<row-1;p++)
		
		{
			for(q=1;q<col-1;q++)
			{
				
				if(temp[p*row+q]==1 || temp[p*row+q]==0)
				{
					count++;
					matrix[p*row+q]=temp[p*row+q];
					printf("%d ",matrix[p*row+q]);
				}
				else{
					printf("%d ",matrix[p*row+q]); }
								
			}
			printf("\n");
		}
		
	}
	
	
	
	
}

