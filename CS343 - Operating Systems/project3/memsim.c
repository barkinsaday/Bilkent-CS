#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/queue.h>
#include "memsim.h"
#define _GNU_SOURCE

//Function Prototypes
void put_to_Ram(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, struct Queue* fq, FILE* o_file, int refTime[], struct Queue* cq);
void fifo(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, struct Queue* fq);
void LRU(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, int refTime[]);
void clock(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, struct Queue* cq);
			

//Global Variables
int fcount = 4;//default: 4
char* algo = "FIFO";//default: FIFO

char* o_VA ;//output line elements
char* o_PTE1;
char* o_PTE2;
char* o_OFFSET;
char* o_PFN;
char* o_PA;
char* o_PF;

int main(int argc, char* argv[])
{
	    //Parsing CMD Line Arguments
	    int level = 0; // for -p option
	    char *addrfile = NULL; // for -r option
	    char *swapfile = NULL; // for -s option
	    int frcount = 0; // for -f option
	    char *algor = NULL; // for -a option
	    int tick = 0; // for -t option
	    char *outfile = NULL; // for -o option

	    for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
		    level = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
		    addrfile = argv[++i];
		} else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
		    swapfile = argv[++i];
		} else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
		    frcount = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
		    algor = argv[++i];
		} else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
		    tick = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
		    outfile = argv[++i];
		}
	    }

	//Create / open outputfile
	algo = algor;
	fcount = frcount;
	
	FILE* o_file = fopen(outfile, "w"); 
	if(o_file == NULL){printf("ERROR: Output could not opened\n"); return -1;}
	
	//Allocate RAM
	void* ram = malloc((sizeof(char)*64)*fcount);
	
	//Init Frames (2 same sized arrays instead of a struct)
	void* frames[fcount];//each frames[i] points to a location in RAM (RAM is divided into frames)
	int isUsed[fcount];//keep info on if frame is empty or not; (False = empty, True = used)
	int refTime[fcount];//Refernce Time (The page in a frame is lastlt referenced x operations ago...) (for LRU)
	for(int i=0; i<fcount; i++){
		frames[i] = ram + (i*sizeof(char)*64);
		isUsed[i] = 0;
		refTime[i] = 0;
	}
		
	//Init page table - init as empty
	struct pageEntry pageTable[1024]; //example: pageTable[23] = 2 means page-23 is mapped to frame-2
	for(int i=0; i<1024; i++){
		pageTable[i].frame_no = -1;
		pageTable[i].dirtyBit = 0;
		pageTable[i].referencedBit = 0;
		pageTable[i].validBit = 0;	
	}
	
	struct Queue* fq = createQ();//FIFO-queue
	struct Queue* cq = createQ();//CLOCK-queue (acts as circular list)
	
	//Read "addrfile" and split the information
	FILE* fp = NULL;
	char* line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	fp = fopen(addrfile, "r");
	if(fp == NULL){printf("Eror on opening file\n"); return -1;}	
	while((read = getline(&line, &len, fp)) != -1)
	{
		char* type = strtok(line, " \n");
		char* address = strtok(NULL, " \n");
		char* data = strtok(NULL, " \n");
		char addr[16];//address in binary addr = NULL;
		char vpn[11];
		char offset[7];
		hex_to_bin(address, addr);
		for(int i=0; i<10; i++)
			vpn[i] = addr[i];
		for(int i=10; i<16; i++)
			offset[i-10] = addr[i];
		vpn[10] = '\0';
		offset[6] = '\0';
		
		o_VA = malloc(sizeof(char)*10);
		sprintf(o_VA, "%s", address);
		put_to_Ram(address, type, vpn, offset, data, frames, isUsed, pageTable, fq, o_file, refTime, cq);
		free(o_VA);
	}
	fclose(fp);
	fclose(o_file);
	free(ram);	

	return 0;
	
}//end of main...


//Function Implementations
void put_to_Ram(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, struct Queue* fq, FILE* o_file, int refTime[], struct Queue* cq)
{
	if(strcmp(algo, "LRU")==0 || strcmp(algo, "lru")==0 ){
		for(int i=0; i<fcount; i++)
			refTime[i] = refTime[i]+1;//+1 to all last reference time for all
	}
	
	int i_vpn = binaryToDecimal(vpn);//vpn as int to use as index in pageTable[]
	
	//Assigning output elements (some are assigned later)
	o_PTE1 = malloc(sizeof(char)*10);
	sprintf(o_PTE1, "0x%x", i_vpn);
	o_PTE2 = malloc(sizeof(char)*10);
	sprintf(o_PTE2, "0x%x", 0);
	int i_offset = (int)strtol(offset, NULL, 2);
	o_OFFSET = malloc(sizeof(char)*10);
	sprintf(o_OFFSET, "0x%x", i_offset);
	o_PFN = malloc(sizeof(char)*10);
	o_PA = malloc(sizeof(char)*15);
		
	if(strcmp(type, "w") == 0)//if writing is done set dirtyBit = 1
		pageTable[i_vpn].dirtyBit = 1;
		
	int flag = 0;
	//Check if vpn in a frame - else put in an empty frame - else do page replacement
	if(pageTable[i_vpn].validBit == 1){//Already in frame
		//printf("Page-%d found in Frame-%d\n", i_vpn, pageTable[i_vpn].frame_no);//DEBUGING
		pageTable[i_vpn].referencedBit = 1;
		//...
		//...TO DO put refed page to end of cq with rb = 1
		//...
		refTime[pageTable[i_vpn].frame_no] = 0;//reset last reference count
		sprintf(o_PFN, "0x%x", pageTable[i_vpn].frame_no);
		sprintf(o_PA, "%p", frames[pageTable[i_vpn].frame_no]);
		
	}else{
		for(int i=0; i<fcount; i++){//Not in a frame
			if(isUsed[i] == 0){//There is an empty frame
				isUsed[i] = 1;
				pageTable[i_vpn].frame_no = i;
				pageTable[i_vpn].validBit = 1; 
				//printf("Page-%d is put in Frame-%d\n", i_vpn, i);//DEBUGING
				sprintf(o_PFN, "0x%x", pageTable[i_vpn].frame_no);
				sprintf(o_PA, "%p", frames[pageTable[i_vpn].frame_no]);
				put(fq, i_vpn);//put page no in FIFO-queue
				put_C(cq, i_vpn, 1);//put page no in CLOCK-queue, refBit = 1
				refTime[i] = 0;//reset last ref time for LRU
				flag = 1;
				break;
			}
		}
		if(flag == 0){//Page Replacement
			//...TO DO before page replacement update data in VPN if dirty bit == 1
			//if no empty frame: page replacement algorithm
			if(strcmp(algo, "FIFO")==0 || strcmp(algo, "fifo")==0){
				fifo(address, type, vpn, offset, data, frames, isUsed, pageTable, i_vpn, fq);
			}else if(strcmp(algo, "LRU")==0 || strcmp(algo, "lru")==0){
				LRU(address, type, vpn, offset, data, frames, isUsed, pageTable, i_vpn, refTime);
			}else if(strcmp(algo, "CLOCK")==0 || strcmp(algo, "clock")==0){
				clock(address, type, vpn, offset, data, frames, isUsed, pageTable, i_vpn, cq);
			}else if(strcmp(algo, "ECLOCK")==0 || strcmp(algo, "eclock")==0){
				clock(address, type, vpn, offset, data, frames, isUsed, pageTable, i_vpn, cq);
			}
		}
	}
	
	char* outLine = malloc(15 * 7 * sizeof(char));
	if(o_PF != NULL){
		sprintf(outLine, "%s %s %s %s %s %s %s", o_VA, o_PTE1, o_PTE2, o_OFFSET, o_PFN, o_PA, o_PF);
	}else{
		sprintf(outLine, "%s %s %s %s %s %s", o_VA, o_PTE1, o_PTE2, o_OFFSET, o_PFN, o_PA);
	}

	//Write to out file
	fprintf(o_file, "%s\n", outLine);
	
	//Free outputLine elements
	free(o_PTE1); o_PTE1 = NULL;
	free(o_PTE2); o_PTE2 = NULL;
	free(o_OFFSET); o_OFFSET = NULL;
	free(o_PFN); o_PFN = NULL;
	free(o_PA); o_PA = NULL;
	free(o_PF); o_PF = NULL;
}//end of "put_to_Ram"...


//FIFO
void fifo(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, struct Queue* fq)
{
	int victim = peek(fq);//gives victim page's i_vpn
	//Update VM if dirty bit = 1
	if(pageTable[victim].dirtyBit == 1){
		//...TO DO update data in VM
		//find the line in swaped file and edit ??? -- write function for that
	}
	
	//Add the new page
	pageTable[i_vpn].frame_no = pageTable[victim].frame_no;//new page will occupy this frame
	pageTable[i_vpn].validBit = 1;
	
	//Remove Victim
	pageTable[victim].validBit = 0;
	pageTable[victim].referencedBit = 0;
	pageTable[victim].dirtyBit = 0;
	memset(frames[pageTable[victim].frame_no], 0, sizeof(char)*64);//clear RAM of replaced frame (probably not needed)
	pageTable[victim].frame_no = -1;
	
	//Adjust output and next time use
	pop(fq);//remove victim from fifo-queue
	put(fq, i_vpn);//put new page into fifo-queue
	sprintf(o_PFN, "0x%x", pageTable[i_vpn].frame_no);//set o_PFN
	o_PF = malloc(sizeof(char)*15);
	sprintf(o_PA, "%p", frames[pageTable[i_vpn].frame_no]);//set o_PA
	sprintf(o_PF, "%s", "pgfault");//set o_PF
}

//LRU
void LRU(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, int refTime[])
{
	//find least recently used pages from occupied frames
	int i_max = 0;//this is a frame no
	int max = 0;
	for(int i=0; i< fcount; i++){
		if(refTime[i] > max){
			max = refTime[max];
			i_max = i;
		}
	}
	//set victim (this is a page no)
	int victim = 0;
	for(int i=0; i<1024; i++){
		if(i_max == pageTable[i].frame_no){
			victim = i;
			break;
		}
	}
	//Add the new page
	pageTable[i_vpn].frame_no = pageTable[victim].frame_no;//new page will occupy this frame
	pageTable[i_vpn].validBit = 1;
	
	//Remove Victim
	pageTable[victim].validBit = 0;
	pageTable[victim].referencedBit = 0;
	pageTable[victim].dirtyBit = 0;
	memset(frames[pageTable[victim].frame_no], 0, sizeof(char)*64);//clear RAM of replaced frame (probably not needed)
	pageTable[victim].frame_no = -1;
	
	//Adjust output and next time use
	refTime[i_max] = 0;//reset ref time to 0
	sprintf(o_PFN, "0x%x", pageTable[i_vpn].frame_no);//set o_PFN
	o_PF = malloc(sizeof(char)*15);
	sprintf(o_PA, "%p", frames[pageTable[i_vpn].frame_no]);//set o_PA
	sprintf(o_PF, "%s", "pgfault");//set o_PF
}

//CLOCK
void clock(char* address, char* type, char* vpn, char* offset, char* data, void* frames[], int isUsed[], 
			struct pageEntry* pageTable, int i_vpn, struct Queue* cq)
{
	int victim = -1;
	int check_RB = 1;
	while(check_RB != 0){//find victim and adjust the list
		victim = peek(cq);
		check_RB = peek_C(cq);
		pop_C(cq);//if rb=1 added to end of list with rb=0 (second chance)
	}
	
	//Add the new page
	pageTable[i_vpn].frame_no = pageTable[victim].frame_no;//new page will occupy this frame
	pageTable[i_vpn].validBit = 1;
	
	//Remove Victim
	pageTable[victim].validBit = 0;
	pageTable[victim].referencedBit = 0;
	pageTable[victim].dirtyBit = 0;
	memset(frames[pageTable[victim].frame_no], 0, sizeof(char)*64);//clear RAM of replaced frame (probably not needed)
	pageTable[victim].frame_no = -1;
	
	//Adjust output adn next time use
	put_C(cq, i_vpn, 1);//put new page into CLOCK-queue
	sprintf(o_PFN, "0x%x", pageTable[i_vpn].frame_no);//set o_PFN
	o_PF = malloc(sizeof(char)*15);
	sprintf(o_PA, "%p", frames[pageTable[i_vpn].frame_no]);//set o_PA
	sprintf(o_PF, "%s", "pgfault");//set o_PF
}





/*
NOTES:
	VIRTUAL ADDRESS:
		-VA = back store = swap file(?)
		-VA is 16-bit (always) 
		-offset is least significant 6 bits
		-rest is VPN (10-bits) VA -> [10, 6] ([vpn-10, offset-6])
		-in two level: VPN is split into P1 and P2 (each 5-bits) VA -> [5, 5, 6]
		-num of pages is 2^10
		
		
	PHYSICAL ADDRESS:
		-PA = RAM
		-PA is 16-bit (always) (does not depend on frame count F)
		-A page entry is always 16-bits
		-10-bit is needed to address each page (2^10 pages)
		-k least significant bits is used as the frame number where 2^k = F
		-Remaining is "1 refernece bit (R)", "1 modified bit (M)", "1 validation bit (V)" (order does not matter)
		-So PA / PTE -> [1, 1, 1, k]  
		
	-Initially all frames are empty
	-Pure demand paging is used
	-Assume all pages in VM is legal (can be put in frames and they are 16-bits)
	
	ALGORITHM:
		+While Frames are Empty (there is and empty frame), (this is not page replancement since we have available frame):
			-Smallest empty frame is allocated first (frame0, frame1, frame2...)
			-"If there is no empty" frame than replacement algorithm (given by cmd as input) takes place
			
		+Page Replacement:(happens when no empty frame available, this a page fault) (common in all algorithms)
			-Use given algo
			-If M-bit = 1 write back to VM before removing from PM (since it means data is modified)
			-After removing the victim page put that caused page fault into the emptied frame
			
			
DEBUGING SHORTCUTS:
	//Print Each outline element seperatly
	printf("--RESULT--\n");
	printf("VA %s\", o_VA);	
	printf("PTE1 %s\", o_PTE1);
	printf("PTE2 %s\", o_PTE2);
	printf("OFFSET %s\", o_OFFSET);
	printf("PFN %s\", o_PFN);
	printf("PA %s\", o_PA);
	printf("PF %s\", o_PF);
	
	//Print Incoming Request Contents
	printf("---------PUTTING TO RAM--------\n");
	printQ(fq);
	printf("--REFERNCE:--\n");
	printf("type: %s\n", type);
	printf("address: %s\n", address);
	if(data != NULL){printf("data: %s\n", data);}
	else{printf("In read statement data is null: %s\n", data);}
	printf("VPN: %s\n", vpn);
	printf("Offset: %s\n", offset);
	printf("--------DONE---------\n");//this will be putting outputline
	
ADDRESS FILE EXAMPLE	
r 0x0000
w 0x0001
w 0x0002 0x5
r 0x2003
w 0x2104 0xff
r 0x1205
r 0x0000
r 0x3d27
w 0x3328
r 0x2429
r 0xaa29
r 0xab29
w 0xab29
r 0xab21
r 0x1205
*/



