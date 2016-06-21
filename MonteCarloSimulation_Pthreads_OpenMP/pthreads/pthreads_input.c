#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/time.h>
#include<pthread.h>
#define total_threads 60
pthread_mutex_t pi_mutex;


double iterations;

double x,y,z;
int count=0;

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








//double getRand(double min, double max);

double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}

void *Cal_pi(void *t) //Calculating the value of Pi.
{

int i=0;
double min=0.00001, max=1.0;
int tid = (long)t;
double lines = iterations/total_threads;

double start = tid*lines;

double stop = start+lines-1;


for ( i=start; i<=stop; i++)  // start-stop points for each individual thread. They all divide the iterations and join at the end.
	{
	   pthread_mutex_lock(&pi_mutex);
       x = getRand(min,max);
	   pthread_mutex_unlock(&pi_mutex);	
	   //printf(" x is ---- %f",x);
	   pthread_mutex_lock(&pi_mutex);
       y = getRand(min,max);
	   pthread_mutex_unlock(&pi_mutex);
	 
       z = x*x+y*y;
	 
       if (z<=1) 
	   {
		count++;
       }
	}  
	pthread_exit(NULL);
}




int main(int argc, char* argv[])
{
  
start();
  
int rc; 
long t; 
	
pthread_t threads[total_threads];	
pthread_mutex_init(&pi_mutex,NULL);
  
	
	double pi;
	int j;
	iterations = atof(argv[1]);
	//total_threads = atoi(argv[2]);
	
	//printf("iterations are --- %f",iterations);
	
	//printf("threads are --- %d",total_threads);
	
	
  for(t=0;t<total_threads;t++)
	{
		rc = pthread_create(&threads[t],NULL,Cal_pi,(void *)t);
		if(rc)
			{
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
			}
	}  
   
 for(j=0;j<total_threads;j++)
	{
		rc = pthread_join(threads[j], NULL);
		if(rc)
		{ 
			printf("\n Error occured in pthread_join %d",rc);
		}
	}
	
	//printf("count is -- %d",count);
	
	
	
    pi=(double)count/iterations*4;
	printf("pi is %g \n",pi);
	pthread_mutex_destroy(&pi_mutex);
	
	stop();
	pthread_exit(NULL);
}




