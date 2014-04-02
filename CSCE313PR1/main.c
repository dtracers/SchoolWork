#include "ackerman.h"
#include "my_allocator.h"
/*
int main(int argc, char ** argv) {
  ackerman_main();
  //this will print left overs
  //print_list();
	//test_main();
}
*/
void test_main()
{
	init_allocator(32,519045);
	Addr d=my_malloc(32);
	my_free(d);
	d=my_malloc(128);
	print_list();
}

