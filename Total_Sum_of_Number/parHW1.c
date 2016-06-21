#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
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

void *SumUpto(void *number)
{
	int i;
	int temp=0;	//A temporary variable to store the total sum
	long no = (long) number; // Converting the pointer variable(number) into integer 
	
	for(i=1;i<=no;i++)
	{
		temp = temp + i;
	}
	printf("Sum is %d\n",temp);	
	pthread_exit(NULL);
}



void main(int argc, char *argv[])
{	
	start();
	int i,rc,total_threads; //Total number of threads
	long t,number; // i and t variables are for the for loop
	
	pthread_t threads[total_threads];
	
	if(argv[1] == NULL )
	{
		number=2;
	}
	else
	{
		number = atof(argv[1]);
	}
	
	if(argv[2] == NULL )
	{
		total_threads=2;
	}
	else
	{
		total_threads = atoi(argv[2]);
	}
	
	for(t=0;t<total_threads;t++)
	{
		rc = pthread_create(&threads[t],NULL,SumUpto,(void *)number);
		if(rc)
			{
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
			}
	}
	
	
	for(i=0;i<total_threads;i++)
	{
		rc = pthread_join(threads[i], NULL);
		if(rc)
		{ 
			printf("\n Error occured in pthread_join %d",rc);
		}
	}
	stop();
	pthread_exit(NULL);

}

