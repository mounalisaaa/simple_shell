#include "shell.h"
extern char **environ;
int handle_builtin(char **tokens, char *buffer)
{
	if (_strcmp(tokens[0], "exit") == 0)
		return (exit_func(tokens, buffer));
	else if (_strcmp(tokens[0], "env") == 0)
		return (env_func());
	/* else if (_strcmp(tokens[0], "setenv") == 0)
	 	return (_setenv());
	 else if (_strcmp(tokens[0], "unsetenv") == 0)
	 	return (_unsetenv(tokens[1]));*/
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
	free_av(tokens);
	free(buffer);
	exit(0);

	return (0);
}
// int _setenv(const char *name, const char *value, int overwrite)
// {
// 	if (!overwrite && _getenv(name))
// 	{
// 		return (0);
// 	}

// 	int result = setenv(name, value, 1);
// 	if (result != 0)
// 	{
// 		return (-1);
// 	}
