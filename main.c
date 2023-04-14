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
 * printenv - prints everything that's inside the environ variable
 */
void printenv()
{
	extern char **environ;
	int i;
	for (i = 0; environ[i] != NULL; i++)
		printf("\n%s", environ[i]);
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
	char *token;
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

/**
 * main - hello
 * Return: exit code
 */
int main(void)
{
	int waitID;
	extern char **environ;
	char buffer[1000];
	char *b = buffer;/*necessary for usage with getline*/
	size_t bufSize = 1000;/*TODO dont forget that this is linked to buffer*/
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