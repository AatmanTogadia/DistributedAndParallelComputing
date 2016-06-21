#include <stdio.h>
#include<stdlib.h>
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

void SumUpto(int number)
{	
	int i,temp=0; //A temporary variable to store the total sum
	for(i=1;i<=number;i++)
	{
			temp = temp + i;	
	}
	printf("Sum is %d\n",temp);	//Printing the total sum
}

int main(int argc, char* argv[])
{
	start();
	int number,i,loop; //number = The number to be calculated and loop = The for loop upper limit(p)
	
	
	if(argv[1] == NULL )
	{
		number = 2;
	}
	else
	{
		number = atoi(argv[1]); //Converting the number(which will be in string) into integer
	}
	
	
	
	if(argv[2] == NULL )
	{
		loop = 2;
	}
	else
	{
		loop = atoi(argv[2]); // Converting the upper limit into integer beacuse it will be in stirng
	}
	
	for(i=1;i<=loop;i++)
	{
	SumUpto(number); //Calling the SumUpto function
	}

	
	stop();
	return 0;
}
