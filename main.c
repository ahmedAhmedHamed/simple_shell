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
 * printenv - ...
 */
void printenv()/*unfinished*/
{
	extern char **environ;
	int i;
	for (i = 0; environ[i] != NULL; i++)
		printf("\n%s", environ[i]);
}

/**
 * strtoking - separates b into argv using a space as a delimiter
 * @argv: ...
 * @b: ...
 */
void strtoking(char *argv[10], char *b)
{
	int i = 0;
	char *token;
	token = strtok(b, " ");
	/* walk through other tokens */
	while( token != NULL )
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
}

/**
 * main - hello
 * Return: exit code
 */
int main(void)
{
	int waitID;
	extern char **environ;
	char buffer[1000];
	char *b = buffer;
	size_t bufSize = 1000;
	size_t characters;
	int processID;
	struct stat istat;/*for usage with stat to check if file exists*/
	char *argv[10];
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
			return (0);
		}

		if (!strcmp(argv[0], "env"))
		{
			printenv();
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