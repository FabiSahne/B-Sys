#include <stdio.h>
#include <unistd.h>

int main()
{
	int p = fork();
	if (p < 0)
	{
		printf("fork failed");
	}
	else if (p == 0)
	{
		// child
		printf("hello\n");
	}
	else
	{
		// parent
		sleep(1);
		printf("goodbye\n");
	}
}
