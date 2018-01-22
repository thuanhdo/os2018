#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 10


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
		printf("Item's type is fried chicken, amount is %d piece(s).\n\n", buffer[i].amount);    
	else 
		printf("Item's type is french fries, amount is %d gram(s).\n\n", buffer[i].amount);
}

void produce(item *i) {
	while ((first +1)% BUFFER_SIZE ==last){
		printf("Can't push new food into the buffer now.");
	} 
	
	memcpy(&buffer[first], i, sizeof(item));
	printf("First item:\n");
	logVal(first);
	printf("Last item:\n");
	logVal(last);
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
	printf("First item:\n");
	logVal(first);
	printf("Last item:\n");
	logVal(last);
	
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

	produce(&chick);
	produce(&fries);
	produce(&smokychick);
}

void *consume_thread(void *param){
	consume();
	consume();
}

int main(){
	pthread_t tid1;
	pthread_t tid2;
	printf("Produce 3 products\n");	
	pthread_create(&tid1, NULL, produce_thread, NULL);
	pthread_join(tid1, NULL);
	printf("Consume 2 of them\n");	
	pthread_create(&tid2, NULL, consume_thread, NULL); 
	pthread_join(tid2, NULL);

	return 0;
}


