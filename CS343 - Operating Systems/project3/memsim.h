#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

//Page Table
struct pageEntry{
	//page_no will be index of pageTable
	int frame_no;//kept seperatly for east access
	int dirtyBit;
	int referencedBit;
	int validBit;
};

//Function Implementations
void hex_to_bin(char* hexdec, char result[16])//input: string hex, output: string binary
{
	char res[16] = {""};
	
	//Skips "0x" if present at beggining of Hex string
	size_t i = (hexdec[1] == 'x' || hexdec[1] == 'X')? 2 : 0;

	while (hexdec[i]) {

		switch (hexdec[i]) {
		case '0':
			strcat(res, "0000");
			break;
		case '1':
			strcat(res, "0001");
			break;
		case '2':
			strcat(res, "0010");
			break;
		case '3':
			strcat(res, "0011");
			break;
		case '4':
			strcat(res, "0100");
			break;
		case '5':
			strcat(res, "0101");
			break;
		case '6':
			strcat(res, "0110");
			break;
		case '7':
			strcat(res, "0111");
			break;
		case '8':
			strcat(res, "1000");
			break;
		case '9':
			strcat(res, "1001");
			break;
		case 'A':
		case 'a':
			strcat(res, "1010");
			break;
		case 'B':
		case 'b':
			strcat(res, "1011");
			break;
		case 'C':
		case 'c':
			strcat(res, "1100");
			break;
		case 'D':
		case 'd':
			strcat(res, "1101");
			break;
		case 'E':
		case 'e':
			strcat(res, "1110");
			break;
		case 'F':
		case 'f':
			strcat(res, "1111");
			break;
		case '.':
			printf(".");
		default:
			printf("\nInvalid hexadecimal digit %c",
				hexdec[i]);
		}
		i++;
	}
	strcpy(result, res);	
	//free(res);
}

//Turn binary string to decimal int
int binaryToDecimal(char* binary)
{
	int decimal = 0;
	int base = 1;
	int len = strlen(binary);
	for(int i=len-1; i>=0; i--){
		if(binary[i] == '1')
			decimal += base;
		base = base*2;
	}
	return decimal;
}


//Queue (for FIFO) (holds int which will reference to frame number)
struct QNode{
	int key;
	int refBit;
	struct QNode* next;
};

struct Queue{
	struct QNode* front;
	struct QNode* rear;
};

struct QNode* newNode(int item, int rb)//utility function
{
	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->key = item;
	temp->refBit = rb;
	temp->next = NULL;
	return temp;
}

struct Queue* createQ()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void put(struct Queue* q, int k)
{
	struct QNode* temp = newNode(k, 0);
	if(q->front == NULL){
		q->front = temp;
		q->rear = temp;
		return;
	}
	q->rear->next = temp;
	q->rear = temp;
}

void put_C(struct Queue* q, int k, int rb)//put version of clock
{
	struct QNode* temp = newNode(k, rb);
	if(q->front == NULL){
		q->front = temp;
		q->rear = temp;
		return;
	}
	q->rear->next = temp;
	q->rear = temp;
}

void pop(struct Queue* q)//removes completely (will be used in CLOCK as well if rb = 0)
{
	if(q->front == NULL)
		return;
	struct QNode* temp = q->front;
	q->front = q->front->next;
	free(temp);
}

void pop_C(struct Queue* q)//pops and adds back to tail with rb=0
{
	if(q->front == NULL)
		return;
	struct QNode* temp = q->front;
	if(temp->refBit == 1)
		put_C(q, temp->key, 0);
	q->front = q->front->next;
	free(temp);
}

void printQ(struct Queue* q)//for testing
{
	if(q->front == NULL){
		printf("Empty Queue\n");
		return;
	}
	struct QNode* curr = q->front;
	while(curr != NULL){
		printf("PN: %d,	RB: %d\n", curr->key, curr->refBit);
		curr = curr->next;
	}
}

int peek(struct Queue* q)//return key of head
{
	return q->front->key;
}

int peek_C(struct Queue* q)
{
	return q->front->refBit;
}




//remove() -- completely
//put_to end -- set R=0 and put to tail (remove and add with rb = 0)







