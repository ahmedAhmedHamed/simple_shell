#include "main.h"

/**
 * printenv - prints everything that's inside the environ variable
 */
void printenv(void)
{
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
 * _setenv - setenv
 * @argv: hello
 */
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

/**
 * _unsetenv - unsetenv
 * @argv: argv
 */
void _unsetenv(char *argv[10])
{
	int errorCatcher;

	errorCatcher = unsetenv(argv[1]);
	if (errorCatcher == -1)
		fprintf(stderr, "unsetenv failed :(\n");
}
