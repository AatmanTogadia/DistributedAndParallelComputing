#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

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





double getRand(double min, double max);



double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}

int main(int argc, char* argv[])
{
	start();
	double min=0.00001, max=1.0;
  
	
  
	double iterations,total_threads;
	double x,y,z,pi;
	int i,count=0;
	int j;
	
	iterations = atof(argv[1]);
	total_threads = atof(argv[2]);
	
	//printf("iterations are --- %f\n",iterations);
	//printf("threads are --- %f\n",total_threads);
	
	
	
	 for(j=0;j<total_threads;j++)
	 {
	for(i=0;i<iterations;i++) 
		
	
	{
       x = getRand(min,max);
	   
	 
       y = getRand(min,max);
       z = x*x+y*y;
       if (z<=1) count++;
	   
	  
    }
	}
	
	
    pi=(double)count/iterations*4;
	
	pi = (double) pi/total_threads;
	
	printf("pi is %g \n",pi);
	 
	stop();
}




