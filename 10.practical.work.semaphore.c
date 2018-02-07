#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>

#define BUFFER_SIZE 10

sem_t s;

typedef struct {
	char type;
	int amount;
	char unit;
} item;


item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
int justProduced = 0;

void logVal(int i){
	if (buffer[i].type==0)
		printf("%d piece(s) of fried chicken.\n", buffer[i].amount);    
	else 
		printf("%d gram(s) of french fried.\n", buffer[i].amount);
}

void produce(item *i) {
	while ((first +1)% BUFFER_SIZE ==last){
		printf("Can't push new food into the buffer now.");
	} 
	
	memcpy(&buffer[first], i, sizeof(item));
	printf("First item:");
	logVal(first);
	printf("Last item:");
	logVal(last);
	printf("\n");
	first = (first+1)% BUFFER_SIZE;	
	justProduced = 1;
}

void consume(){
	while (first == last){
		//printf("We don't have anything to serve.");
	}
	if (justProduced == 1) {
		first = (first-1)%BUFFER_SIZE;
		justProduced = 0;
	}
	last = (last +1)% BUFFER_SIZE;
	printf("First item:");
	logVal(first);
	printf("Last item:");
	logVal(last);
	printf("\n");
	
}

void *produce_thread(void *param){
	item chick;
	chick.type = 0;
	chick.amount = 5;
	chick.unit = 0;
	
	item fries;
	fries.type = 1;
	fries.amount = 200;
	fries.unit = 1;
	
	item smokychick;
	smokychick.type = 0;
	smokychick.amount = 12;
	smokychick.unit = 0;

	while(1){
		sem_wait(&s);
		produce(&chick);
		produce(&fries);
		produce(&smokychick);
		sem_post(&s);
		break;
		}
}

void *consume_thread(void *param){
	consume();
	consume();
}

int main(){
	pthread_t tid1;
	pthread_t tid2;

	sem_init(&s, 0, 1); //pshared=0 =>btw threads ; !=0 =>btw processes 
	pthread_create(&tid1, NULL, produce_thread, NULL);
	pthread_create(&tid2, NULL, consume_thread, NULL); 
	pthread_join(tid2, NULL);

	return 0;
}


