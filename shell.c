#include "shell.h"

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *token = NULL, **tokens= NULL;
	const char *delim = " \t\n";
	bool run = true;
	int i = 0;

	while (run)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);
		else
			run = false;
		if ((getline(&buffer, &buffer_size, stdin)) == -1)
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
		execute_cmd(tokens, buffer);
		i = 0;
		free(tokens);
		tokens = NULL;
	}
	free(buffer);
	return (0);
}
