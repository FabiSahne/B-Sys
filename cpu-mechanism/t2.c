#define _GNU_SOURCE
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

#define ITER 1000000

int main()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double start = tv.tv_sec + (tv.tv_usec / 1000000.0);

	// set sched_setaffinity to single thread
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	// set up pipe
	int fd[2];
	pipe(fd);

	// set up child process
	pid_t pid = fork();
	if (pid == -1)
    {
        perror("fork");
        return 1;
    }
	if (pid == 0)
	{
		for (int i = 0; i < ITER; i++)
		{
			read(fd[0], NULL, 0);
		}
		return 0;
	} else {
		for (int i = 0; i < ITER; i++)
		{
			write(fd[1], NULL, 0);
		}
		wait(NULL);
	}

	gettimeofday(&tv, NULL);
	double end = tv.tv_sec + (tv.tv_usec / 1000000.0);
	
	printf("Time taken: %f s for %d context switches.\n", end - start, ITER);
	printf("Time taken: %f ms (%f μs) for 1 context switch\n",
		1000 * (end - start) / (double)ITER,
		1000000 * (end - start) / (double)ITER);


	return 0;
}