#include "shell.h"

int main(int argc, char **argv)
{
	bool run = true;
	char *buffer = NULL, *buffer_copy = NULL;
	const char *delim = " \t\n";
	size_t buffer_size = 0, token_len;
	int count;
	ssize_t rn;
	char *tokens[100] = {0}, *token = NULL;

	while (run)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);
		else
			run = false;
		if ((rn = getline(&buffer, &buffer_size, stdin)) == -1)
		{
			if (!isatty(STDIN_FILENO))
			{
				free(buffer);
				break;
			}
			perror("getline");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		if (*buffer == '\n' || (*buffer == ' ' || *buffer == '\t'))
			continue;
		buffer_copy = _strdup(buffer);
		token = strtok(buffer_copy, delim);
		for (count = 0; token; count++)
		{
			token_len = _strlen(token);
			tokens[count] = malloc(sizeof(char *) * token_len);
			_strncpy(tokens[count], token, token_len + 1);
			token = strtok(NULL, delim);
		}
		free(buffer_copy);
		execute_cmd(tokens, buffer);
		free_av(tokens);
		free(buffer);
		buffer = NULL;
		buffer_size = 0;
	}
	free(buffer);
	return (0);
}