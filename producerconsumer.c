//references
//http://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html#BASICS
//http://cis.poly.edu/cs3224a/Code/ProducerConsumerUsingPthreads.c
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define BUFFERSIZE 3


//shared resource
int buffer;

//conditional variables and mutex
pthread_cond_t condc = PTHREAD_COND_INITIALIZER;
pthread_cond_t condp = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


 
void *producer();
void *consumer();

int main(){
	
	pthread_t t1, t2, t3,t4,t5,t6,t7;



	//create threads
  	pthread_create( &t1, NULL, &producer, NULL);
	pthread_create( &t2, NULL, &producer, NULL);
	pthread_create( &t3, NULL, &producer, NULL);
	pthread_create( &t4, NULL, &producer, NULL);
  	pthread_create( &t5, NULL, &consumer, NULL);
	pthread_create( &t6, NULL, &consumer, NULL);
	pthread_create( &t7, NULL, &consumer, NULL);
	
	

	pthread_exit(NULL);

	return 0;
}


void *producer(){
	int i;
	int j = 0;


while(j < 3){
	
	//locks buffer 
	pthread_mutex_lock(&mutex);
	
	
	while(buffer == BUFFERSIZE){
		pthread_cond_wait(&condp, &mutex);
	}



	buffer++;
	printf("Buffer: ");
	//prints x's in buffer
	for( i = 0; i < buffer; i++){
		printf("x");
	}
		printf(" \tproducer added 1 to buffer\n");

	j++;
	
		
	pthread_cond_signal(&condc);
	pthread_mutex_unlock(&mutex);		
	

	

	}

	pthread_exit(NULL);	
}

void *consumer(){
	int i;
	int j = 0;

while(j < 3){


	pthread_mutex_lock(&mutex);
	
	while(buffer == 0){
		pthread_cond_wait(&condc, &mutex);
	}



	buffer--;
	printf("Buffer: ");
	for( i = 0; i < buffer; i++){
		printf("x");
	}
		printf(" \tconsumer subtracted 1 from buffer\n");
	
	
	
	
	j++;

		
	pthread_cond_signal(&condp);
	pthread_mutex_unlock(&mutex);
	
	
	

	}
	pthread_exit(NULL);
	
}
