/* 
    File: my_allocator.h

    Author: R.Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/08

    Modified:

*/

#ifndef _my_allocator_h_                   // include file only once
#define _my_allocator_h_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

typedef void * Addr; 
typedef unsigned char BYTE;

/*--------------------------------------------------------------------------*/
/* FORWARDS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* MODULE   MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/

unsigned int init_allocator(unsigned int _basic_block_size, 
			    unsigned int _length); 
/* This function initializes the memory allocator and makes a portion of 
   ’_length’ bytes available. The allocator uses a ’_basic_block_size’ as 
   its minimal unit of allocation. The function returns the amount of 
   memory made available to the allocator. If an error occurred, 
   it returns 0. 
*/ 

int release_allocator(); 
/* This function returns any allocated memory to the operating system. 
   After this function is called, any allocation fails.
*/ 

Addr my_malloc(unsigned int _length);

/**
 * This will split the memory into two separate memories
 * it will return the address of one and store the other in the free list
 */
Addr split(Addr _a,BYTE size_requested);
/**
 * This will combine two memories into one memory
 */
Addr combine(Addr _a,int lower);
/* Allocate _length number of bytes of free memory and returns the 
   address of the allocated portion. Returns 0 when out of memory. */ 

//void set_bit(Addr _a,BYTE bit_one,BYTE bit_two,BYTE bit_three,BYTE size);

int my_free(Addr _a); 

void add_free_memory_to_list(Addr currentblock,Addr adding);
void add_free_memory_to_list_recurse(Addr currentblock,Addr adding);

Addr remove_free_memory_from_list(Addr currentblock,Addr previous,Addr look_for);
Addr remove_free_memory_from_list_recurse(Addr currentblock,Addr previous,Addr look_for);

//void link_next_pointer(Addr current,Addr link_to);
//long get_next_pointer(Addr current);
void print_header(Addr _a);

extern void print_list();
/* Frees the section of physical memory previously allocated 
   using ’my_malloc’. Returns 0 if everything ok. */ 

#endif 
