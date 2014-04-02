/* 
    File: my_allocator.c

    Author: <your name>
            Department of Computer Science
            Texas A&M University
    Date  : <date>

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

//basic_block_size is in bytes
int basic_block_size;
unsigned int indexes;
//this is an ordered tree
//using current index*2 +1 or current index*2
void** list_of_free;
//byte values
Addr big_block;
//first bit  left = 0 right = 1
#define first_bit_loc 128;
//this is from parent
#define second_bit_loc 64;
//this may change???

//free bit free = 0 not free = 1
#define third_bit_loc 32;
#define size_loc 31;


    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/* InLine Methods  */
/**
 * This will set the bit information
 */
inline void set_bit(Addr _a,BYTE bit_one,BYTE bit_two,BYTE bit_three,BYTE size)
{
	BYTE* characters=_a;
	BYTE old_header=characters[0];
	characters[0]=(bit_one)|(bit_two)|(bit_three)|size;
	BYTE new_header=characters[0];
}
inline void link_next_pointer(Addr currentblock,Addr link_to)
{
	BYTE* current=currentblock;
	Addr temp=(current+1);
	long* pointer_holder=temp;
	pointer_holder[0]=link_to;//warning bahahaha little do they know
}

inline long get_next_pointer(Addr currentblock)
{
	BYTE* current=currentblock;
	Addr temp=(current+1);
	long* pointer_holder=temp;
	return pointer_holder[0];
}
/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR MODULE MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/

/* Don't forget to implement "init_allocator" and "release_allocator"! */
unsigned int init_allocator(unsigned int _basic_block_size,
			    unsigned int _length)
{
	atexit(release_allocator);
	basic_block_size=_basic_block_size;
	big_block=malloc(_length);
	unsigned int length=_length/_basic_block_size;
	////printf("length %d part1 %d, part2 %d\n",length,logpart1);
	indexes=log2(length)+1;
//	printf("the number of indexes is %d\n",indexes);
	BYTE* characters=big_block;
	characters[0]=indexes-1&size_loc;
	int list_size=(indexes)*sizeof(void*);
	Addr list=malloc(list_size);
	list_of_free=list;
	list_of_free[indexes-1]=big_block;
	return (int)_length;
}

int release_allocator()
{
	if(big_block!=NULL)
	{
		free(big_block);
		big_block=NULL;
	}
	if(list_of_free!=NULL)
	{
		free(list_of_free);
		list_of_free=NULL;
	}
}
extern Addr my_malloc(unsigned int _length) {

	//add one to the length to account for the header
	unsigned int level=log2((_length+1)/basic_block_size);
	int index=level;
	Addr pointer=list_of_free[index];
	while(pointer==NULL&&index<indexes)
	{
		pointer=list_of_free[index];
		index++;
	}
	if(pointer==NULL)
	{
		//printf("NO MEMORY IS ABLE TO BE ALLOCATED\n");
		return malloc((size_t)_length);
	}
	if(index==level)
	{
		//printf("No splitting was needed\n");
		pointer=remove_free_memory_from_list(pointer,(void*)(NULL),list_of_free[index]);
	}
	else
	{
		//printf("splitting memory of size %d\n",(index-1));
		pointer=split(pointer,(BYTE)level);
		BYTE size=((BYTE*)pointer)[0]&size_loc;
	}
	BYTE* characters=pointer;
	//this will set the memory to not free!
	characters[0]|=third_bit_loc;//this says that the memory is no longer free
	characters+=1;
	pointer=characters;
	return pointer;
}

/**
 * This is pointing to the beginning of it!!!
 */
Addr split(Addr _a,BYTE size_requested)
{
	BYTE* characters=_a;
	BYTE header=characters[0];
	BYTE size=header&size_loc;

	if(size<=0)
		return _a;//it cant be a size less than zero no more splitting...


	BYTE new_size=size-1;
	BYTE* new_address=_a+(basic_block_size<<new_size);

	BYTE parent_bit_one=header&first_bit_loc;
	BYTE parent_bit_two=header&second_bit_loc;

	//if the size_requested is less than 128 then it is the first time going through the list
	if(size_requested<128)
		remove_free_memory_from_list(list_of_free[(int)size],NULL,_a);
	//third bit determines if it is free
	//left = 0, and parent pulls left parent bit
//	printf("the parent_bit_one is %d\n",parent_bit_one);
	set_bit(_a,0,parent_bit_one>>1,0,new_size);

	set_bit(new_address,128,parent_bit_two,0,new_size);
	void* pointer=list_of_free[(int)new_size];
	if(pointer==NULL)
		list_of_free[(int)new_size]=new_address;
	else
	{
		add_free_memory_to_list(list_of_free[(int)new_size],new_address);
		//instead we just link the pointer!!
		//link_next_pointer(_a,new_address);
	}
	if((size_requested&31)<new_size)
	{
		return split(_a,(size_requested|128));
		//add_free_memory_to_list(list_of_free[(int)new_size],_a);
	}
	return _a;
}

/**
 * This will free stuff
 */
extern int my_free(Addr _a)
{

	BYTE* mem=_a;
	mem-=1;
	//size is DEBUG ONLY!!!
	BYTE DEBUG_size=mem[0]&size_loc;
	//printf("\n\nfreeing memory of size %d\n",DEBUG_size);

	//this will reset the previous memory to zero so that pointers can be used
	link_next_pointer(mem,NULL);

	//this will set the third bit to zero and leave everything else the same
	BYTE header=mem[0];
	set_bit(mem,header&128,header&64,0,header&31);//this says that the memory is free
	mem=combine(mem,0);


	BYTE size=mem[0]&size_loc;
	//printf("memory was combined up to size %d\n",size);
	void* freedom=list_of_free[(int)size];
	if(freedom!=NULL)
		add_free_memory_to_list(freedom,mem);
	else
		list_of_free[(int)size]=mem;
	//I like a tree of the free memory that is removed when it is added but then how do we link to it again?

	//long my_pointer_value=big_block;

	/* Same here! */
	//free(_a);
	return 0;
}

/**
 * This is pointing to the beginning of it!!!
 *
 * worst case is O(n) meaning every block is in its smallest form and need to be combined
 * this should actually never happen
 */
Addr combine(Addr _a,int lower)
{
	BYTE* characters=_a;
	BYTE header=characters[0];
	BYTE size=header&size_loc;
	BYTE first_bit=header&first_bit_loc;
	BYTE* buddy;

	//then it is at the max size it can not be combined
	if(size>=indexes-1)
	{
		return _a;
	}

	if(first_bit==0)
	{
		//then it is the left one
		buddy=(characters+(basic_block_size<<size));
	}else
	{
		//then it is the right one
		buddy=(characters-(basic_block_size<<size));
	}
	BYTE buddy_header=buddy[0];
	BYTE buddy_size=buddy_header&size_loc;
	BYTE free=buddy_header&third_bit_loc;
	//if the buddy is not free you can not merge
	if(free!=0)
	{
		return _a;
	}
	if(buddy_size!=size)
	{
		buddy=combine(buddy,1);
		buddy_size=(buddy[0])&size_loc;
		//if after trying to combine buddy it failed then you can not merge
		if(buddy_size!=size)
		{
			return _a;
		}
		//only happens if the buddy size changes!!!
		buddy_header=buddy[0];
	}
	BYTE parent_first_bit;
	BYTE parent_second_bit;
	//if it is left then we do not swap them
	if(first_bit==0)
	{
		parent_first_bit=header&second_bit_loc;
		parent_second_bit=buddy_header&second_bit_loc;
		_a=characters;
	}else
	{
		parent_first_bit=buddy_header&second_bit_loc;
		parent_second_bit=header&second_bit_loc;
		_a=buddy;
	}
	Addr removed=remove_free_memory_from_list(list_of_free[(int)buddy_size],NULL,buddy);

	//I need to removed buddy from list
	set_bit(_a,parent_first_bit<<1,parent_second_bit,0,size+1);
	//that way it will go up the ladder
	if(lower<=0)
		combine(_a,lower);
	return _a;
	//if first_bit is left then it should look to the right
}

/**
 * This will go through till it finds the end and adds itself to the end
 * this is recursive
 */
void add_free_memory_to_list(Addr currentblock,Addr adding)
{
	long value=get_next_pointer(currentblock);
	if(value==0)
	{
		//this is the end of the line!!!
		link_next_pointer(currentblock,adding);
		link_next_pointer(adding,NULL);
	}else
	{
		Addr next=value;//another warning teehee
		if(next>adding)
		{
			//this means that adding needs to come before adding
			//it should continue going up until it reaches one that is higher

			//this will link the one that is adding to the one that is bigger
			link_next_pointer(adding,next);

			//this will link the current to adding
			link_next_pointer(currentblock,adding);
			return;
		}
		if(next==adding)
		{
			//printf("IT SHOULD NOT BE ALREADY HERE!!!!!!\n\n\n\n");
			return;
		}
		add_free_memory_to_list(next,adding);
	}
}

/**
 * this will remove free memory from the list
 * it wont say whether the memory itself is free...
 */
Addr remove_free_memory_from_list(Addr currentblock,Addr previous,Addr look_for)
{
	/*
	if(currentblock==NULL)
	{
		printf("ITS NULL EVERYTHING IS REMOVED!\n");
		return NULL;
	}
	*/
	long value=get_next_pointer(currentblock);
	if(value==0)
	{
		//the current block is the end!!!
		if(previous!=NULL)
		{
			link_next_pointer(previous,NULL);
			return currentblock;
		}else
		{
			//this is if it is the only memory left in the thing
			BYTE* current=currentblock;
			BYTE size=current[0]&size_loc;
			/*
			Addr is_null=list_of_free[(int)size];
			if(is_null==NULL)
			{
				printf("EVERYTHING HAS BEEN REMOVED?\n");
				return NULL;
			}
			*/
			list_of_free[(int)size]=NULL;
			return currentblock;
		}
	}else
	{
		Addr next=value;//another warning bahahahah
		if(look_for!=NULL&&look_for==value)
		{
			//this will link the current block to thing point
			//the block you are looking for is pointed too
			link_next_pointer(currentblock,get_next_pointer(look_for));
			//if it is removed then it is not pointing to anything
			link_next_pointer(look_for,NULL);
			return look_for;
		}
		return remove_free_memory_from_list(next,currentblock,look_for);//continue
	}
}


/**
 * This is the pointer to the memory address
 */
void print_header(Addr _a)
{
	BYTE* header=_a;
	//printf("header value is %d\n",header[0]);
	BYTE start=header[0];
	BYTE firstbit=start&first_bit_loc;
	BYTE secondbit=start&second_bit_loc;
	BYTE thirdbit=start&third_bit_loc;
	BYTE the_size=start&size_loc;
	//printf("first bit is %d\n",firstbit);
	//printf("second bit is %d\n",secondbit);
	//printf("free bit is %d\n",thirdbit);
	//printf("size is %d\n",the_size);
}
void print_header_file(Addr _a,FILE* fp)
{
	BYTE* header=_a;
	//printf("header value is %d\n",header[0]);
	BYTE start=header[0];
	BYTE firstbit=start&first_bit_loc;
	BYTE secondbit=start&second_bit_loc;
	BYTE thirdbit=start&third_bit_loc;
	BYTE the_size=start&size_loc;
	fprintf(fp,"first bit is %d\n",firstbit);
	fprintf(fp,"second bit is %d\n",secondbit);
	fprintf(fp,"free bit is %d\n",thirdbit);
	fprintf(fp,"size is %d\n",the_size);
}

extern void print_list()
{
	int k=0;
	//printf("PRINTING FILES!!!!!\n");
	while(k<indexes)
	{
		//printf("\nI AM AT INDEX %d\n",k);
		FILE *fp;

		fprintf(fp,"INDEX=%d\n",k);
		Addr current=list_of_free[k];
		int mem_counter=0;
		while(current!=NULL&&list_of_free[k]!=NULL)
		{
			//printf("Printing mem#%d\n",mem_counter);
			print_header_file(current,fp);
			print_header(current);
			current=remove_free_memory_from_list(list_of_free[k],NULL,NULL);
			mem_counter++;
		}
		k++;
	}
}
