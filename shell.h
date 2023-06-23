#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>

void execute_cmd(char **av, char *buff);
char *_getenv(const char *name);
char *get_cmd(char *command);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
void free_av(char **av);
char *_strncpy(char *dest, char *src, int n);
void _puts(char *str);
int _putchar(char c);
ssize_t read_user_input(char **userInput_buf, size_t *buf_size);

#endif