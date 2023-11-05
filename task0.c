#include "main.h"

/**
 * simple_shell - The main function
 */

void simple_shell(void)
{
	size_t n;
	char *args[100];
	char *buf = NULL;
	int status;

	while (1)
	{
		printf("$ ");
		if (getline(&buf, &n, stdin) == -1)
		{
			printf("\n");
			break;
		}

		int i = 0;

		args[i] = strtok(buf, " \n");

		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " \n");
		}
		args[i] = NULL;

		pid_t pid = fork();

		if (pid == -1)
			printf("Failed to create child process");
		else if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
				printf("Failed to execute\n");

		}
		wait(&status);
		free(buf);
	}
}
