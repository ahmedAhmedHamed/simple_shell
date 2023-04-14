//
// Created by vboxuser on 14/04/23.
//

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - hello
 * Return: exit code
 */
int main(void)
{
	int waitID;
	while (true)
	{
		char buffer[1000];
		char *b = buffer;
		size_t bufSize = 1000;
		size_t characters;
		int processID;
		printf("$ ");
		characters = getline(&b, &bufSize,  stdin);
		if (feof(stdin)) /*checking for end of file*/
			return (0);
		processID = fork();
		if (!processID)
		{
			struct stat i;
			b[characters - 1] = '\0';
			extern char **environ;
			if (stat(b, &i))
			{
				fprintf(stderr, "No such file or directory\n");
				continue;
			}
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