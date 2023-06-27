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
		if (valid_num(tokens[1]))
			existatus = atoi(tokens[1]);

		else
		{
			fprintf(stderr, "Error: invalid exit status\n");
			existatus = 2;
			return (existatus);
		}
	}
	free_av(tokens);
	free(buffer);
	exit(existatus);
}
int valid_num(char *args)
{
	if (args[0] == '-')
		args++;
	while (*args)
	{
		if (!isdigit(*args))
			return (0);
		args++;
	}
	return (1);
}
