#include "shell.h"
void execute_cmd(char **tokens, char *buffer)
{
	int status;
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			perror("execve");
			free(buffer);
			free(tokens);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}