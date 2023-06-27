#include "shell.h"

int handle_builtin(char **tokens, char *buffer)
{
	if (_strcmp(tokens[0], "exit") == 0)
		return (exit_func(tokens, buffer));
	else if (_strcmp(tokens[0], "env") == 0)
		return (env_func());
	/*
	 *else if (_strcmp(tokens[0], "setenv") == 0)
	 *	return (_setenv());
	 *else if (_strcmp(tokens[0], "unsetenv") == 0)
	 *	return (_unsetenv(tokens[1]));
	 */
	else
		return (-1);
}
int env_func(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_puts(environ[i]);

	return (0);
}
int exit_func(char **tokens, char *buffer)
{
	int i = 0;
	int existatus = 0;
	while (tokens[i])
		i++;
	if (i == 1)
	{
		free_av(tokens);
		free(buffer);
		exit(0);
	}
	if (_atoi(tokens[1]) == -1)
	{
		fprintf(stderr, "./hsh: 1: exit: Illegal number: -98\n");
		return (2);
	}
	existatus = atoi(tokens[1]);
	free_av(tokens);
	free(buffer);
	exit(existatus);
}
/**
 * _atoi - converts string to an integer
 * @nptr: string to be converted
 * Return: converted integer value or -1
 */
int _atoi(char *nptr)
{
	int i = 0, n = 0;

	if (nptr[i] == '+')
		i++;

	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (-1);

		n = (n * 10) + (nptr[i] - '0');
		i++;
	}

	return (n);
}