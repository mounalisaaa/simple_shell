#include "shell.h"

int main(int ac, char **av)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *token = NULL; //**tokens = NULL;
	char *buffer_copy = NULL;
	const char *delim = " \t\n";
	bool run = true;
	int i = 0, j = 0;

	(void)ac;
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
		buffer_copy = strdup(buffer);
		token = strtok(buffer, delim);
		while (token)
		{
			i++;
			token = strtok(NULL, delim);
			// tokens = realloc(tokens, sizeof(char *) * (i + 1));
			// if (!tokens)
			// {
			// 	perror("realloc");
			// 	free(buffer);
			// 	exit(EXIT_FAILURE);
			// }
			// tokens[i] = token;
			// token = strtok(NULL, delim);
			// i++;
		}
		i++;
		av = malloc(sizeof(char *) * i);
		token = strtok(buffer_copy, delim);
		while (token)
		{
			av[i] = malloc(sizeof(char *) * strlen(token));
			strcpy(av[i], token);
		}
		av[i] = NULL;
		// execute_cmd(arr);
		free(av);
		free(buffer_copy);
		free(buffer);
		// tokens = NULL;
	}
	// free(buffer_copy);
	// free(buffer);
	return (0);
}
