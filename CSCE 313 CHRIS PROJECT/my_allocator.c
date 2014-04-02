/* 
    File: my_allocator.c

    Author: Christopher A. Trask
            Department of Computer Science
            Texas A&M University
    Date  : <date>

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

   
    #define HEADER_SIZE         1 //byte
    #define IS_LEFT         0x80// left most bit
    #define PARENT          0x40//second left most bit
    #define IS_LIST         0x20// third left most bit
    #define GET_BLOCK_SIZE      0x1F// 5 right most bits

    #define SHIFT_SIZE_OF_ARRAY 11
    #define GET_SIZE_OF_ARRAY 0xF800
    #define SHIFT_FRONT_SIZE 5
    #define GET_FRONT_SIZE 0x03E0
    #define GET_MIN_BLOCK_SIZE 0x001F

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include<stdlib.h>
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/
    
    /* -- (none) -- */
    
/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR MODULE MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/
Addr gHead=NULL;

Addr* get_free_array(){return (Addr*)(((byte*)gHead)+2);}
byte get_size_of_free_array(){return (byte)(((*((short*)gHead))&GET_SIZE_OF_ARRAY)>>SHIFT_SIZE_OF_ARRAY);}
byte get_min_block_size(){return (byte)((*((short*)gHead))&GET_MIN_BLOCK_SIZE);}
byte get_front_block_size(){return (byte)(((*((short*)gHead))&GET_FRONT_SIZE)>>SHIFT_FRONT_SIZE);}
byte get_block_size(Addr block){if(block!=gHead)return (*((byte* )block))&GET_BLOCK_SIZE;else return get_front_block_size();}
Addr get_listed_block(Addr block){return (*((Addr*)(((byte*)block)+1)));}
byte get_is_list(Addr block){if(block!=gHead)return (*((byte*)block))&IS_LIST;else return 0;}
byte get_gHeader_size(){return (get_size_of_free_array()+1);}
byte get_is_left(Addr block){if(block!=gHead)return (*((byte*)block))&IS_LEFT;else return 1;}
byte get_parent(Addr block){if(block!=gHead)return (*((byte*)block))&PARENT;else return 1;}
Addr get_end_of_list(Addr block)
{
    if(get_is_list(block))
        return get_end_of_list(get_listed_block(block));
    return block;
}
byte* get_header(Addr block){return (byte*)block;}

void print_list(byte i,Addr block)
{
    if(block!=NULL)
    {
    printf("\t%u : %p \n",i,block);
    if(get_is_list(block))
    {    
        print_list(i,get_listed_block(block));
    }}
}
void print_free_array()
{
    byte size_of_free_array=get_size_of_free_array();
    Addr* free_array=get_free_array();
    byte i;
    for(i=0;i<size_of_free_array;i++)
    {
        printf("%u : %p \n",i,free_array[i]);
        if(free_array[i]!=NULL&&free_array[i]!=gHead)
        {
            if(get_is_list(free_array[i]))
                print_list(i,get_listed_block(free_array[i]));
        }   
    }
}

/* Don't forget to implement "init_allocator" and "release_allocator"! */
extern unsigned int init_allocator(unsigned int _basic_block_size, 
			    unsigned int _length)
{
    //printf("gHead: %d \n",gHead);
    
    if( gHead == NULL )
    {
        byte size_of_free_array;
        byte max_block_size;//stored as a power of 2
        byte min_block_size;//stored as a power of 2
        unsigned int temp_free_blocks=0;
        
        /*if the min block size plus 3 bytes is less than the max size can't 
            allocate (adds 3 for the required intialization of 2 bytes for the 
                allocater and 1 for the min size of the array of blocks)*/
        if( ( _basic_block_size + 6 ) > _length )
        {
            return 0;
        }
        
        /*Find the max size by a power of 2 and the max power of 2*/
        unsigned long long actual_max_size=1;
        byte power_size=0;
        while( actual_max_size <= _length )
        {
            actual_max_size = actual_max_size<<1;
            power_size++;
        }
        
        /*divide the max size by 2 to put it back under _length*/
        actual_max_size = actual_max_size >> 1;
        power_size--;
        
        /*Store the max block size*/
        max_block_size=power_size;
        
        /*Add block sizes to actual_max_size to get it closer to _length*/
        unsigned int block_size = actual_max_size;
        while( block_size >= _basic_block_size )
        {
            if( (actual_max_size + block_size) < _length )
            {
                actual_max_size += block_size;
                /* Tracks the blocks added */
                temp_free_blocks = temp_free_blocks^(1<<power_size);
            }
            
            block_size = block_size>>1;
            power_size--;
        }
        power_size++;
        
        /*Store the min block size*/
        min_block_size = power_size;
        
        /*Store the size of the free block array*/
        size_of_free_array = max_block_size - min_block_size + 1;
        
        printf("size_array: %u \n", (int) size_of_free_array);
        printf("min_size: %u \n", (int) min_block_size);
        printf("max_size: %u \n", (int) max_block_size);
        printf("free_blocks %x \n", (int) temp_free_blocks);
        
        /*Allocate the memory*/
        gHead=malloc( actual_max_size );

        /*Store Allocator Memory*/
        if(gHead!=NULL)
        {
        short* Sizes = ( short* )( gHead );
        ( *Sizes ) =  min_block_size;
        ( *Sizes ) = (*Sizes) ^ ((size_of_free_array-1)<<SHIFT_FRONT_SIZE);
        ( *Sizes ) = (*Sizes) ^ (size_of_free_array<<SHIFT_SIZE_OF_ARRAY);
        
        /*Store free block array*/
        unsigned long long temp_actual_max_size=actual_max_size;
        Addr* free_array = get_free_array();
        byte i;
        for( i = 0 ; i < size_of_free_array ; i++ )
        {
            int is_block_free = ( temp_free_blocks & ( 1 << ( min_block_size + i ) ) );
            if( is_block_free )
            {                
                actual_max_size -= 1<<( min_block_size + i );
                Addr t = (Addr)(((byte*)(gHead)) + actual_max_size);
                if(i != (size_of_free_array - 1) )
                {
                    byte* header = ( byte* )( t );
                    ( *header ) = i;
                    ( *header ) = ( *header ) ^ IS_LEFT;
                }
                free_array[i] = t;
                //printf("free_blocks: %u \n", i);
            }
            else
            {
                free_array[i] = NULL;
            }
        }
        actual_max_size = temp_actual_max_size;
        
        free_array[size_of_free_array-1] = gHead;
        }
        printf("%p %p \n",gHead,gHead+actual_max_size);
        
        //print_free_array();
        
        /*printf("size_array: %u \n", get_size_of_free_array());
        printf("min_size: %u \n", get_min_block_size());*/
        
        return actual_max_size;
        
    }
    else
    {
        return 0;
    }
}

extern int release_allocator()
{
    free(gHead);
    gHead = NULL;
    return 0;
} 

byte get_desired_block_size ( unsigned int _length )
{
    byte size_of_free_array = get_size_of_free_array();
    byte min_block_size = get_min_block_size();
    
    /*Get correct block size*/
    unsigned int temp=(1<<(size_of_free_array+min_block_size-1));
    if( (_length + 1 + ((4*get_gHeader_size())) )> temp)
    {
        return 0xFF;
    }
    else if(( _length + 1 )>= (1<<(size_of_free_array+min_block_size-2)))
    {
        return size_of_free_array-1;
    }
    unsigned int t_length = (_length + 1)>>(min_block_size);
    byte i;
    for( i=1; ; i++ )
    {
        t_length = t_length>>1;
        if(t_length==1||t_length<1)
            break; 
    }
    
    return i;
}

Addr make_block(byte desired_block_size)
{
    byte size_of_free_array = get_size_of_free_array();
    Addr* free_array = get_free_array();
    
    //print_free_array();
    
    if( desired_block_size+1 < size_of_free_array )
    {
        Addr parent_block;
        if( free_array[ desired_block_size + 1 ] == NULL )
        {
            parent_block = make_block( desired_block_size + 1 );
        }
        else
        {
            parent_block = free_array[ desired_block_size + 1];
            free_array[ desired_block_size + 1]=NULL;
        }
        
        if( (parent_block == gHead) && ( get_gHeader_size() > (1<<desired_block_size+get_min_block_size())))
        {
            parent_block = make_block(desired_block_size+1);
        }
        if(parent_block == NULL)
        {
            return NULL;
        }
        
        byte block_size = get_block_size( parent_block );
        byte is_left = get_is_left( parent_block );
        byte parent = get_parent( parent_block );
        byte is_list=0;
        
        if(parent_block != gHead )
        {
            is_list = get_is_list( parent_block );
        }
        
        byte is_front_block = 0;
        if( is_list )
        {
            free_array[desired_block_size + 1]=get_listed_block( parent_block );
            if( get_end_of_list( free_array[desired_block_size+1] ) == gHead)
            {
                is_front_block = 1;
            }
        }
        
        free_array[desired_block_size] = parent_block;
        
        byte* header = (byte*)(parent_block);
        if( ( ( Addr ) header ) == gHead )
        {
             unsigned short* Sizes = ( short* )( gHead );
             (*Sizes) = (((*Sizes)&0xf81f)^(((short)desired_block_size)<<SHIFT_FRONT_SIZE));
        }
        else
        {
            (*header) = desired_block_size; 
            (*header) = ( ( *header ) ^ IS_LEFT );
            if(is_left)
            {
                (*header) = ( (*header) ^ PARENT );
            }
            if( is_front_block )
            {
                (*header) = ((*header) ^ IS_LIST);
                (*((Addr*)(header+1))) = gHead;
            }
            
        }
        
        unsigned int memory = 1;
        memory = memory<<desired_block_size;
        byte min = get_min_block_size();
        memory = memory<<min;
        Addr return_block = (Addr)(((byte*)free_array[ desired_block_size ]) + memory);
        
        byte* return_block_header = (byte*)return_block;
        
        (*return_block_header) = desired_block_size;
        if(parent)
        {
            (*return_block_header) = (*return_block_header) ^ PARENT;
        }
        //print_free_array();
        return (return_block);
        
    }
    else
    {
        //print_free_array();
        return NULL;
    }
}


extern Addr my_malloc(unsigned int _length) 
{
    byte size_of_free_array = get_size_of_free_array();
    byte min_block_size = get_min_block_size();
    Addr* free_array = get_free_array();
    byte desired_block_size;
    
    // print_free_array();
    /*Get correct block size*/
    desired_block_size = get_desired_block_size( _length );
    
    /*Check Free Array*/
    Addr return_block = free_array[desired_block_size];
    //printf("malloc %p %p %u dbs%u sfa%u\n",return_block,gHead,return_block==gHead,desired_block_size,size_of_free_array);
    if( return_block == NULL )
    {
        Addr r = make_block( desired_block_size );
        if(r == NULL)
        {
            return NULL;
        }
        //printf("%p 1st// %p\n",r,r+1);
        byte* a = ((byte*)r);
        (*a)=(*a)&(0xDF);
        return (r+1);  
    }
    else if( return_block == gHead)
    {
        if( (_length+get_gHeader_size()+1) <= (1<<(desired_block_size+min_block_size)) )
        {
            Addr r = ( Addr )( return_block );
            free_array [ desired_block_size ] = NULL;
            //printf("%p gHead// %p\n",r,r+4*get_gHeader_size()+1);
            return r+4*get_gHeader_size()+1;
        }
        else
        {
            Addr r = make_block( desired_block_size );
            //printf("%p makegHead// %p\n",r,r+1);
            if(r == NULL)
                return NULL;
            byte* a = ((byte*)r);
            (*a)=(*a)&(0xDF);
            return (r+1);  
        }
    }
    else
    {
                
        if( ( (*get_header(return_block)) & GET_BLOCK_SIZE ) == desired_block_size ) 
        {
            if( get_is_list(return_block) )
            {
                Addr t = get_listed_block(return_block);
                free_array [ desired_block_size ] = t;
                Addr r = ( Addr )( return_block);
                if(r == NULL)
                    return NULL;
                //printf("%p 2nd// %p\n",r,r+1);
                byte* a = ((byte*)r);
                (*a)=(*a)&(0xDF);
                return r+1;
            }
            else
            {
                Addr r = ( Addr )( return_block );
                free_array [ desired_block_size ] = NULL;
                if(r == NULL)
                    return NULL;
                //printf("%p 3rd// %p\n",r,r+1); 
                byte* a = ((byte*)r);
                (*a)=(*a)&(0xDF);   
                return r+1;
            }
        }
        else
        {
            return NULL;
        }
    }
//  return malloc((size_t)_length);
}
void check_for_pairs(Addr block, Addr last_block);
void find_position(Addr new_block,Addr current_block,Addr last_block);
void check_for_pairs(Addr block, Addr last_block)
{
    //print_free_array();
    Addr* free_array=get_free_array();
    if(block!=gHead)
    {
    if(get_is_list(block))
    {
        Addr next_block=get_listed_block(block);
        if(!get_is_left(block))
        {
            Addr is_next_block = (Addr)(((byte*)block)-(1<<(get_min_block_size()+get_block_size(block))));
            if(is_next_block==next_block)
            {
                byte new_block_size=get_block_size(block)+1;
                if(block==gHead)
                {
                    unsigned short* Sizes = ( short* )( gHead );
                    (*Sizes) = (((*Sizes)&0xf81f)^(((short)new_block_size)<<SHIFT_FRONT_SIZE));
                }
                else
                {
                    byte* header = ( byte* )( next_block );
                    if(next_block!=gHead)
                        (*header ) = new_block_size;
                    if(get_parent(next_block)&&next_block!=gHead)
                    {
                        (*header) = (*header)^IS_LEFT; 
                    }
                    if(get_parent(block)&&next_block!=gHead)
                    {
                        (*header) = (*header)^PARENT; 
                    }
                    if(get_is_list(next_block))
                    {
                        if(last_block!=NULL)
                        {
                            Addr* last_block_ptr=(Addr*)(((byte*)last_block)+1);
                            (*last_block_ptr)=get_listed_block(next_block);
                        }
                        my_free(next_block+1);
                    }
                    else
                    {
                        if(next_block!=gHead)
                        {
                            header=(byte*)next_block;
                            (*header)=(*header)&0xdf;
                            free_array[new_block_size-1]=NULL;
                            my_free(next_block+1);
                        }
                        else
                        {
                            unsigned short* Sizes = ( short* )( gHead );
                            (*Sizes) = (((*Sizes)&0xf81f)^(((short)new_block_size)<<SHIFT_FRONT_SIZE));
                            free_array[new_block_size-1]=NULL;
                            if(new_block_size==(get_size_of_free_array()-1))
                                free_array[new_block_size]=gHead;
                            else
                                my_free(next_block+1);
                        }
                    }
                }
            }
        }
        else
        {
            //check_for_pairs(next_block,block);
        }
    }
    }
    //print_free_array();
}

void find_position(Addr new_block, Addr current_block, Addr last_block)
{
    //if(last_block==NULL)
        //print_free_array();
    if(get_is_list(current_block))
    {
        Addr next_block=get_listed_block(current_block);
        if(current_block > new_block && (next_block<new_block))
        {
            byte* header = (byte*)new_block;
            (*header) = (*header) ^ IS_LIST;
            Addr* new_block_ptr = (Addr*)(header+1);
            (*new_block_ptr) = next_block;
            Addr* current_block_ptr = (Addr*)(((byte*)current_block)+1);
            (*current_block_ptr)= new_block;
            if(!get_is_left(current_block))
                check_for_pairs(current_block,last_block);
            if(!get_is_left(new_block))
                check_for_pairs(new_block,current_block);
        }
        else
        {
            find_position(new_block,next_block,current_block);
        }
    }
    else
    {
        if((current_block-get_gHeader_size()-1)!=gHead)
        {
            if(current_block>new_block)
            {
                byte* header = (byte*)current_block;
                (*header) = (*header) ^ IS_LIST; 
                Addr* current_block_ptr = (Addr*)(((byte*)header)+1);
                (*current_block_ptr)= new_block;
                byte* new_head=((byte*)new_block);
                (*new_head)=(*new_head)&0xdf;
                //get_free_array()[get_block_size(current_block)]=current_block;
                if(!get_is_left(current_block))
                    check_for_pairs(current_block,NULL);
            }
            else 
            {
                byte* header = (byte*)new_block;
                (*header) = (*header) ^ IS_LIST;
                Addr* new_block_ptr = (Addr*)(((byte*)header)+1);
                (*new_block_ptr)= current_block;
                get_free_array()[get_block_size(new_block)]=new_block;
                byte* new_head=((byte*)current_block);
                (*new_head)=(*new_head)&0xdf;
                if(!get_is_left(new_block))
                    check_for_pairs(new_block,NULL);
            }
        }
        else
        {
            
        }
    }
}




extern int my_free(Addr _a) 
{
    if(_a==NULL)
        return -1;
    if(_a<gHead||(_a>(gHead+(1<<(get_min_block_size()+get_size_of_free_array())))))
        return -2;
    Addr* free_array=get_free_array();
    Addr block;
    //printf("%p %p %p \n",_a,((_a-4*get_gHeader_size()-1)),gHead);
    if((_a-4*get_gHeader_size()-1)!=gHead)
        block =(Addr)(_a-1);
    else
        block = gHead; 
    byte block_size = get_block_size(block);
    Addr array_block=free_array[block_size];
    //printf("adkjsl %u %p\n",block_size,array_block);
    if(array_block==NULL)
    {
        //printf("?");
        free_array[block_size]=block;
    }
    else
    {
        //printf("How the fuck");
        find_position(block,array_block,NULL);
    }
    return 0;
}

