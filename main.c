
#include "main.h"


/**
 * main - hello
 * Return: exit code
 */
int main(int argc, char *argv[10])
{
	int waitID;
	char *b = NULL;/*necessary for usage with getline*/
	size_t characters;
	int processID;
	char *nextArgv[10];
	(void) argc;
	(void) argv;

	while (true)
	{
		characters = setupInput(nextArgv, &b);
		formatString(characters, nextArgv, b);
		if (isEqual(nextArgv[0], "exit"))
		{
			frees(nextArgv);
			free(b);
			return (0);
		}
		if (isEqual(nextArgv[0], "env"))
		{
			printenv();
			continue;
		}
		if (fileExists(nextArgv))
			continue;
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(nextArgv[0], nextArgv, environ);
			perror("execve");
			return (0);
		}
		wait(&waitID);
	}
}
