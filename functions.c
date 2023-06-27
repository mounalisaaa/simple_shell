#include "shell.h"

void free_av(char **av)
{
	int i = 0;

	while (av[i])
	{
		free(av[i]);
		i++;
	}
}
int execute_cmd(char **av, char *buff)
{
	int status;
	pid_t pid;
	char *cmd = NULL;
	int eexit = handle_builtin(av, buff);

	if (eexit == -1)
	{
		cmd = get_cmd(av[0]);
		if (!cmd)
		{
			_puts("Command not found"); /*WA 3NDAK TNSAYY HADI*/
			return (0);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(cmd, av, environ) == -1)
			{
				perror("execve");
				free_av(av);
				free(buff);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
		if (_strcmp(cmd, av[0]) != 0)
			free(cmd);
	}
	return (eexit);
}

char *_getenv(char *name)
{
	int i = 0;
	ssize_t len = _strlen(name);

	for (; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
	}
	return (NULL);
}

char *get_cmd(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
		path_copy = _strdup(path);
		command_length = _strlen(command);
		path_token = strtok(path_copy, ":");

		while (path_token)
		{
			directory_length = _strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path); /* free bushe ntchekiw li morah*/
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0) /* ila kant cmd brasha path .. wa mat3rf*/
		{
			return (command);
		}
		return (NULL);
	}

	return (NULL);
}
void tokenize(char *buffer, char **tokens)
{
	size_t token_len;
	const char *delim = " \t\n";
	char *token = NULL;
	int count = 0;
	char *buffer_copy = NULL;

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
}
