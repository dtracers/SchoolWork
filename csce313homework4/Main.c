/*
 * Main.c
 *
 *  Created on: Apr 16, 2012
 *      Author: gigemjt
 */




/* time example */
#include <stdio.h>
#include <time.h>

int main ()
{
	time_t seconds;
	struct tm * timeinfo;
	int counter=0;
	for(;;)
	{
		seconds = time (NULL);
		timeinfo = localtime ( &seconds );
		if(counter%5==0)
		printf("%d seconds\n",timeinfo->tm_sec);
		counter++;
		sleep(60);
	}
	//printf ("%ld hours since January 1, 1970", seconds/3600);
	return 0;
}
