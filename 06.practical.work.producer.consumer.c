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
		printf("We don't have anything to serve.");}
	if(justProduced == 1){
		first = (first-1)%BUFFER_SIZE;
		justProduced = 0;
	}
	last = (last +1)% BUFFER_SIZE;
	printf("First item:\n");
	logVal(first);
	printf("Last item:\n");
	logVal(last);
	
}

int main(){
	item chick;
	chick.type = 0;
	chick.amount = 5;
	chick.unit = 0;
	
	item fries;
	fries.type = 1;
	fries.amount = 200;
	fries.unit = 1;
	
	produce(&chick);
	
	produce(&fries);
	
	consume();

	return 0;
}

