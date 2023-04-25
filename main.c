/**
 *  Created by Stan on 14/04/23.
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024
#include "main.h"

/**
 * _strlen - helo
 * @s: s
 * Return: s
 */
int _strlen(const char *s)
{
	int len;
	if (s == 0)
		return (-1);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * printenv - prints everything that's inside the environ variable
 */
void printenv()
{
	extern char **environ;
	int i;
	for (i = 0; environ[i] != NULL; i++)
		printf("\n%s", environ[i]);
	printf("\n");
}

/**
 * strtoking - separates b into argv using a space as a delimiter
 * it allocates new memory to each one of the argv arguments
 * @argv: to
 * @b: from
 */
void strtoking(char *argv[10], const char *b)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	while (b[i] != '\0')
	{
		l = 0;
		while (b[i] != ' ' && b[i] != '\0')
			i++;
		argv[k] = malloc(sizeof(char) * ((i - j) + 1));
		while (i != j)
		{
			argv[k][l] = b[j];
			j++;
			l++;
		}
		argv[k][l] = '\0';
		k++;
		i++;
		j = i;
	}
}

void _setenv(char *argv[10])
{
	int errorCatcher;
	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "not enough arguments\n");
		return;
	}

	errorCatcher = setenv(argv[1], argv[2], 1);

	if (errorCatcher == -1)
		fprintf(stderr, "setenv failed\n");
}

void _unsetenv(char *argv[10])
{
	int errorCatcher;
	errorCatcher = unsetenv(argv[1]);
	if (errorCatcher == -1)
		fprintf(stderr, "unsetenv failed :(\n");
}

/**
 * main - hello
 * Return: exit code
 */
int main(void)
{
	int errorCatcher;
	int waitID;
	extern char **environ;
	char buffer[BUFSIZE];
	char *b = buffer;/*necessary for usage with getline*/
	size_t bufSize = BUFSIZE;
	size_t characters;
	int processID;
	struct stat istat;/*for usage with stat to check if file exists*/
	char *argv[10];/*TODO change if too low*/
	int i = 0;
	while (true)
	{
		for (i = 0; i < 10; i++)
			argv[i] = NULL;
		printf("$ ");
		characters = getline(&b, &bufSize,  stdin);
		if (feof(stdin)) /*checking for end of file*/
		{
			free(b);
			return (0);
		}
		b[characters - 1] = '\0';
		strtoking(argv, b);/*separating string into tokens into argv*/

		if (!strcmp(argv[0], "exit"))
		{
			free(b);
			if (argv[1] != NULL)
				return (atoi(argv[1]));
			else
				return (0);
		}

		if (!strcmp(argv[0], "env"))
		{
			printenv();
			continue;
		}

		if (!strcmp(argv[0], "setenv"))
		{
			_setenv(argv);
			continue;
		}

		if (!strcmp(argv[0], "unsetenv"))
		{
			_unsetenv(argv);
			continue;
		}

		if (!strcmp(argv[0], "cd"))
		{
			if (argv[1] == NULL)
			{
				fprintf(stderr, "Not enough arguments\n");
				continue;
			}
			errorCatcher = chdir(argv[1]);
			if (errorCatcher == -1)
				fprintf(stderr, "Chdir failed\n");

			continue;
		}

		if (stat(argv[0], &istat))/*checking if file exists*/
		{
			fprintf(stderr, "No such file or directory\n");
			continue;
		}
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(argv[0], argv, environ);
			perror("execve");
			return (0);
		}
		wait(&waitID);
	}
	return (0);
}