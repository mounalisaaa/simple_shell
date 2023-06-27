#include "shell.h"
/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	bool run = true;
	int status = 0;
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t rn;
	char *tokens[100] = {0};

	while (run)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);
		else
			run = false;
		rn = getline(&buffer, &buffer_size, stdin);
		if (rn == -1)
		{
			if (!isatty(STDIN_FILENO))
			{
				free(buffer);
				break;
			}
			perror("getline");
			free(buffer);
			exit(status);
		}
		if (*buffer == '\n' || (*buffer == ' ' || *buffer == '\t'))
			continue;
		tokenize(buffer, tokens);
		status = execute_cmd(tokens, buffer);
		free_av(tokens);
		free(buffer);
		buffer = NULL;
		buffer_size = 0;
	}
	free(buffer);
	return (status);
}
