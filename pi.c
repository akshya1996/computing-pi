#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 16         //number of threads




//this function generates a random numbet
float randomNumber()
{
float fvalue;
fvalue=rand()/(float)RAND_MAX;
return fvalue;
}


//this part of the code is parallelized
void *Print(void *arg)
{
	int myid=(int) arg;
	//printf("\n Hello World from thread %d\n",myid);
        float *c=(float *)malloc(sizeof(float));
	*c=0;
	float n=1618931/NUM_THREADS;
	int i=0;
	float x,y,z;
	for(i=0;i<n;i++)
	{
		x=randomNumber();
		y=randomNumber();
		z=sqrt((x*x)+(y*y));
		if(z<1)
			*c+=1;
	}
	if(myid==0)
	{
		float rem;
		rem=1618931%NUM_THREADS;
		for(i=0;i<rem;i++)
		{
			x=randomNumber();
			y=randomNumber();
			z=sqrt((x*x)+(y*y));
			if(z<1)
				*c+=1;
		}
	}
	//printf("C value=%f\n",*c);
return (void *)c;
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc,t;
   float val=0;
   float result;
   void *num;
   for(t=0;t<NUM_THREADS;t++)
   {
	   rc=pthread_create(&threads[t],NULL,Print,(void *)t);
	   if(rc)
	   {
		   printf("ERROR: return error from pthread_create() is %d\n",rc);
		   exit(-1);
	   }
   }
   for(t=0;t<NUM_THREADS;t++)
   {
	   rc=pthread_join(threads[t],&num);
	   val=val + *(float*)num;
           //printf("Value=%f\n",val);

   }
result=(val/1618931)*4;
printf("PI=%f\n",result);
  return 0;
}


