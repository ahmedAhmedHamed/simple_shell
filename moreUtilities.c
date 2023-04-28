#include "main.h"

/**
 * myStrCpy - copies from to to using malloc WITHOUT any protection
 * @from: string to be copied
 * @to: string to be copied to
 */
void myStrCpy(char *from, char **to)
{
	int i = 0;
	int stop = _strlen(from);
	(*to) = malloc(_strlen(from) * sizeof(char));

	while (i <= stop)
	{
		(*to)[i] = from[i];
		i++;
	}
}

/**
 * fileExists - returns 0 if file exists
 * @nextArgv: ...
 * Return: ...
 */
int fileExists(char *nextArgv[10])
{
	struct stat istat;

	if (stat(nextArgv[0], &istat))/*checking if file exists*/
	{
		write(STDERR_FILENO, nextArgv[0], _strlen(nextArgv[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		frees(nextArgv);
		return (1);
	}
	return (0);
}

/**
 * freeAll - frees both parameters
 * @b: ...
 * @nextArgv: ...
 */
void freeAll(char *b, char *nextArgv[])
{
	if (nextArgv != NULL)
		frees(nextArgv);
	if (b != NULL)
		free(b);
}
/**
 * freeExit - frees both parameters then exits the program
 * @b: ...
 * @nextArgv: ...
 */
void freeExit(char *b, char *nextArgv[])
{
	freeAll(b, nextArgv);
	exit(0);
}
