#include "main.h"

/**
 * changeDir - does cd
 * @argv: argv
 */
void changeDir(char *argv[10])
{
	int errorCatcher;

	if (argv[1] == NULL)/*could be wrong, if 1 is null should go home*/
	{
		fprintf(stderr, "Not enough arguments\n");
		return;
	}
	if (argv[1][0] == '-' || argv[1][0] == '~')
		argv[1][0] = '/';
	errorCatcher = chdir(argv[1]);
	if (errorCatcher == -1)
		fprintf(stderr, "Chdir failed\n");
}

/**
 * checkFunctions - applies correct function
 * @argv: argv
 * Return: returns one if a function was used, zero if none were used.
 */
int checkFunctions(char *argv[10])
{
	if (!strcmp(argv[0], "env"))
	{
		printenv();
		return (1);
	}

	if (!strcmp(argv[0], "setenv"))
	{
		_setenv(argv);
		return (1);
	}

	if (!strcmp(argv[0], "unsetenv"))
	{
		_unsetenv(argv);
		return (1);
	}

	if (!strcmp(argv[0], "cd"))/*likely need to handle $VARIABLE*/
	{
		changeDir(argv);
		return (1);
	}
	return (0);
}

/**
 * formatString - reformats the string "b" then puts it in argv
 * @argv: argv
 * @b: string to be formatted
 * @characters: number of characters read before
 */
void formatString(int characters, char *argv[10], char *b)
{
	b[characters - 1] = '\0';
	strtoking(argv, b);/*separating string into tokens into argv*/
}

/**
 * setupInput - prints the "$ ", clears argv and takes input into b
 * @argv: argv
 * @b: other string
 * Return: number of characters read from input
 */
int setupInput(char *argv[10], char *b)
{
	int characters;
	int i;
	size_t bufSize = BUFSIZE;

	for (i = 0; i < 10; i++)
		argv[i] = NULL;
	printf("$ ");
	characters = getline(&b, &bufSize,  stdin);
	return (characters);
}
