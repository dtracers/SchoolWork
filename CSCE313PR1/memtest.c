/*
 * memtest.c
 *
 *  Created on: Feb 13, 2012
 *      Author: gigemjt
 */

#include "ackerman.h"
#include "my_allocator.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	char *bvalue = NULL;
	char *svalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "b:s:")) != -1)
	 switch (c)
	   {
	   case 'b':
		 printf("CASE B\n");
		 bvalue = optarg;
		 break;
	   case 's':
		   printf("CASE S\n");
		 svalue = optarg;
		 break;
	   case 'c':
		 break;
	   case '?':
		   fprintf (stderr,
					"Unknown option character `\\x%x'.\n",
					optopt);
		 return 1;
	   default:
		   printf("ABORTING");
		 abort ();
	   }
	int b=atoi(bvalue);
	int s=atoi(svalue);
	ackerman_main(b,s);
//	printf("huh? %d",b);
}
