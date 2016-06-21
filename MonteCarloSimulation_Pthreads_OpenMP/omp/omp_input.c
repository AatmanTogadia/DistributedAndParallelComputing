#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<omp.h>

struct timeval tm1, tm2;

#define numThreads 2
#define iterations 700

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
  
	

//	double iterations;
	double x,y,z,pi;
	int i,count=0;
	int j;
	
//	iterations = atof(argv[1]);
	
	
	//printf("iterations are --- %d\n",iterations);
	//printf("threads are --- %d\n",numThreads);
	

 
	#pragma omp parallel num_threads(numThreads) firstprivate(i,j) shared(x,y,z) reduction(+:count) 
	
	{
			
			#pragma omp sections 
		{
			#pragma omp section
			
			for(i=0;i<iterations;i++)
			{
				 x = getRand(min,max);
				 y = getRand(min,max);
				z = x*x+y*y;
				if (z<=1) 
					#pragma omp atomic
					count++;
			}
			#pragma omp section
			
			for(j=0;j<iterations;j++)
			{
				 x = getRand(min,max);
				y = getRand(min,max);
				z = x*x+y*y;
				if (z<=1) 
					#pragma omp atomic
					count++;
			}

		

			
		}	
	} 
	 // Experimenting with other OMP directives -----************----------------------*********************----------------
	
/*	#pragma omp parallel num_threads(numThreads) firstprivate(i,j) shared(x,y,z) reduction(+:count) 
	
	{
		
		for(j=0;j<iterations;j++)
	{
		    int this_thread = omp_get_thread_num();
			int my_start = (this_thread)*10/numThreads;
			int my_stop = (this_thread+1)*10/numThreads;
		#pragma omp for
		for(i=my_start;i<my_stop;i++) 
	
	
       x = getRand(min,max);
	   y = getRand(min,max);
       z = x*x+y*y;
       if (z<=1)
			#pragma omp atomic
		   count++;
			}
		} */
		
	/*	#pragma omp parallel num_threads(numThreads) firstprivate(i,j) shared(x,y,z) reduction(+:count) 
   {	

	for(j=0;j<iterations;j++)
	{
	#pragma omp for schedule(dynamic,numThreads) ordered
	   for(i=0;i<numThreads;i++) 
	
	
       x = getRand(min,max);
	   y = getRand(min,max);
       z = x*x+y*y;
       if (z<=1)
			#pragma omp atomic
		   count++;
    
  
	}
	} */
   	
		//-----************----------------------*********************----------------
		
		
		
		
    pi=(double)count/iterations*4;
	
	pi = (double)pi/numThreads;

	printf("pi is %g \n",pi);
	 
	 stop();
}








