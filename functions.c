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
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * frees - frees _argv
 * @_argv: Array to be freed
 */
void frees(char *_argv[10])
{
	int i = 0;

	while (_argv[i] != NULL)
	{
		if (_argv[i] != NULL)
		{
			free(_argv[i]);
			_argv[i] = NULL;
		}
		i++;
	}
}

/**
 * strtoking - separates b into argv using a space as a delimiter
 * it allocates new memory to each one of the argv arguments
 * @argv: to
 * @b: from
 */
void strtoking(char *argv[10], char *b)
{
	int i = 0;
	char *token;

	token = strtok(b, " ");
	/* walk through other tokens */
	while (token != NULL)
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
		write(STDERR_FILENO, "not enough arguments\n", 21);
		return;
	}

	errorCatcher = setenv(argv[1], argv[2], 1);

	if (errorCatcher == -1)
		write(STDERR_FILENO, "setenv failed\n", _strlen("setenv failed\n"));
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
		write(STDERR_FILENO, "unsetenv failed\n", _strlen("unsetenv failed\n"));
}
