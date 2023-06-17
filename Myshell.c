#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t char_num = 0;

	char *token, **tokens = NULL;
	const char *delim = " \t\n";
	int i = 0;

	int status;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");
		else
			break;
		char_num = getline(&buffer, &buffer_size, stdin);
		if (char_num == -1)
		{
			perror("getline");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		token = strtok(buffer, delim);
		while (token)
		{
			tokens = realloc(tokens, sizeof(char *) * (i + 1));
			if (!tokens)
			{
				perror("realloc");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			tokens[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
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
		i = 0;
		free(tokens);
		tokens = NULL;
	}
	free(buffer);

	return (0);
}