#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20


int main()
{
	struct timeval gtodTimes[N];
	char *procClockTimes[N];
	int bytes_read = 0;
	int MAX_LENGTH = 400;
	/* allocate memory for character buffers HERE before you use them */

	int fd = open("/dev/mytime", O_RDWR);
	if(fd < 0)
		printf("ERROR WITH OPEN");
	
	/* check for errors HERE */
	
	for(int j = 0; j < N; j++)
	{
		procClockTimes[j] = calloc(400, sizeof(char));
	}

	
	int i = 0;
	for( i=0; i < N; i++)
	{
		//gettimeofday(&gtodTimes[i], 0);
		bytes_read = read(fd, procClockTimes[i], MAX_LENGTH);
		/* check for errors HERE */
	}	

	close(fd);

//	for(i=0; i < N; i++) {
//		printf("...", gtodTimes[i], procClockTime[i]);
		/* fix the output format appropriately in the above line */
//	}

};
