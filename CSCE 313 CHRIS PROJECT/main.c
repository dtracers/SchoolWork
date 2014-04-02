#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_allocator.h"
#include "ackerman.h"

int main(int argc, char ** argv) 
{

    printf("%u \n",init_allocator(128,(1<<29)));
    /*int i;
    Addr a[12];
    Addr b[12];
    print_free_array();
    Addr t=my_malloc(1<<18);
    printf("ptr %p \n",t);
    print_free_array();
    printf("free %d \n",my_free(t));
    print_free_array();
    for(i=0;i<12;i++)
    {
        b[i]=(1<<(i+7));
        //print_free_array();
        a[i]=my_malloc(1<<(i+7));
        printf("main :%p %p\n",b[i],a[i]);
    }
    print_free_array();
    for(i=11;i>-1;i--)
    {
        //print_free_array();
        printf("HAI DAR\n");
        printf("%p %u \n",b[i],my_free(a[i]));
    }*/
    ackerman_main();
    release_allocator();
    system("pause");
}
