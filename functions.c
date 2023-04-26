#include "main.h"

/**
 * printenv - prints everything that's inside the environ variable
 */
void printenv(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * setupInput - prints the "$ ", clears argv and takes input into b
 * @argv: argv
 * @b: other string
 * Return: number of characters read from input
 */
int setupInput(char *_argv[10], char **b)
{
	int characters;
	int i;
	size_t bufSize = 0;

	for (i = 0; i < 10; i++)
		_argv[i] = NULL;

	write(STDOUT_FILENO, "$ ", 2);
	characters = getline(b, &bufSize,  stdin);
	return (characters);
}

int fileExists(char *nextArgv[10])
{
	struct stat istat;

	if (stat(nextArgv[0], &istat))/*checking if file exists*/
	{
		write(1, nextArgv[0], _strlen(nextArgv[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		frees(nextArgv);
		return (1);
	}
	return (0);
}
