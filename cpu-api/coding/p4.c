#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
		char *args[2];
		args[0] = "/bin/ls";
		args[1] = NULL;

		execl(args[0], args[1]);
	}
	else
	{
		//parent
		wait(NULL);
	}
}