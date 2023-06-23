#include "shell.h"

extern char **environ;

void free_av(char **av)
{
	int i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
}
void execute_cmd(char **av, char *buff)
{
	int status;
	pid_t pid;
	char *cmd = NULL;
	cmd = get_cmd(av[0]);
	if (!cmd)
	{
		printf("%s: Command not found\n", av[0]);
		return;
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
	if (strcmp(cmd, av[0]) != 0)
		free(cmd);
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
	path = getenv("PATH");

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
// ssize_t read_user_input(char **buff, size_t *buf_size)
// {
// 	ssize_t rn;

// 	rn = getline(buff, buf_size, stdin);
// 	if (rn == -1)
// 	{
// 		if (!isatty(STDIN_FILENO))
// 			return (-1);
// 		free(buff);
// 		perror("getline");
// 		exit(EXIT_FAILURE);
// 	}
// 	if ((*buff)[rn - 1] == '\n')
// 		(*buff)[rn - 1] = '\0';

// 	buff = NULL;

// 	return (rn);
// }