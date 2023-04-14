/**
 *  Created by Stan on 14/04/23.
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"

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
	struct stat i;/*for usage with stat to check if file exists*/
	while (true)
	{
		printf("$ ");
		characters = getline(&b, &bufSize,  stdin);
		if (feof(stdin)) /*checking for end of file*/
		{
			free(b);
			return (0);
		}
		b[characters - 1] = '\0';
		if (stat(b, &i))/*checking if file exists*/
		{
			fprintf(stderr, "No such file or directory\n");
			continue;
		}
		processID = fork();
		if (!processID)
		{

			char *argv[] = {b, 0};
			printf("%s", b);
			execve(b, &argv, environ);
			perror("execve");
			return (0);
		}
		wait(&waitID);
	}
	return (0);
}