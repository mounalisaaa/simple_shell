#include "shell.h"
extern char **environ;

void execute_cmd(char **tokens, char *buffer)
{
	int status;
	char *arr[]= {"ls", "-ls"};
	char *cmd = NULL;
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		//cmd = get_cmd(tokens[0]);
		if (execve("ls", arr, NULL) == -1)
		{
			perror("execve");
			free(buffer);
			free(tokens);
			exit(EXIT_FAILURE);
		}
	}
	
	// else
	// {
	// 	wait(&status);
	// }
}

char *_getenv(const char *name)
{
	int i = 0;
	char *var_name;
	for (i = 0; environ[i]; i++)
	{
		var_name = strtok(environ[i + 1], "=");
		if (strcmp(var_name, name) == 0)
			return (strtok(NULL, "="));
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
			directory_length = strlen(path_token);
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
