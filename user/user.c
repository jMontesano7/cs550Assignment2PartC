#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 5


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
		
		procClockTimes[j] = calloc(1000, sizeof(char));
	}

	
	int i = 0;
	for( i=0; i < N; i++)
	{
		gettimeofday(&gtodTimes[i], 0);
		if(bytes_read = read(fd, procClockTimes[i], MAX_LENGTH)<0)
		{
			printf("ISSUE WITH READ");
		}
	}	

	if(close(fd)<0)
	{
		printf("ISSUE WITH CLOSE");
	}
	

	for(i=0; i < N; i++) {
		printf("N = %d \n USERSPACE: \n GetNsTimeOfDay: %lu %lu \n KERNELSPACE: \n %s \n",N, gtodTimes[i].tv_sec, gtodTimes[i].tv_usec, procClockTimes[i]);
		/* fix the output format appropriately in the above line */
	}
};
