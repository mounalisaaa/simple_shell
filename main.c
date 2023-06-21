#include "shell.h"
void free_av(char **av);
void execute_cmd1(char **av, char *buff);
char *get_cmd1(char *command);
int main(int ac, char **av)
{
	bool run = true;
	char *buffer = NULL, *buffer_copy = NULL;
	const char *delim = " \t\n";
	size_t buffer_size = 0, token_len;
	int count;
	char *token = NULL;

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
		token = strtok(buffer_copy, delim);
		for (count = 0; token; count++)
		{
			token_len = strlen(token);
			av[count] = malloc(sizeof(char *) * token_len);
			strncpy(av[count], token, token_len + 1);
			token = strtok(NULL, delim);
		}
		av[count] = NULL;
		execute_cmd1(av, buffer_copy);
		free_av(av);
		free(buffer_copy);
	}
	free(av);
	free(buffer);
	return (0);
}
void free_av(char **av)
{
	int i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
}
void execute_cmd1(char **av, char *buff)
{
	int status;
	pid_t pid;
	char *cmd = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// cmd = get_cmd1(av[0]);

		if (execve(av[0], av, NULL) == -1)
		{
			perror("execve");
			free_av(av);
			free(av); //wa7ed l memo leak hnaa
			// free(buff_cpy);
			free(buff);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
// char *get_cmd1(char *command)
// {
// 	char *path, *path_copy, *path_token, *file_path;
// 	int command_length, directory_length;
// 	struct stat buffer;
// 	path = getenv("PATH");

// 	if (path)
// 	{
// 		path_copy = strdup(path);
// 		command_length = strlen(command);
// 		path_token = strtok(path_copy, ":");

// 		while (path_token)
// 		{
// 			directory_length = strlen(path_token);
// 			file_path = malloc(command_length + directory_length + 2);
// 			strcpy(file_path, path_token);
// 			strcat(file_path, "/");
// 			strcat(file_path, command);
// 			strcat(file_path, "\0");
// 			if (stat(file_path, &buffer) == 0)
// 			{
// 				// free(path_copy);
// 				return (file_path);
// 			}
// 			else
// 			{
// 				// free(file_path); /* free bushe ntchekiw li morah*/
// 				path_token = strtok(NULL, ":");
// 			}
// 		}
// 		// free(path_copy);
// 		if (stat(command, &buffer) == 0) /* ila kant cmd brasha path .. wa mat3rf*/
// 		{
// 			return (command);
// 		}
// 		return (NULL);
// 	}

// 	return (NULL);
// }
