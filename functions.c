#include "main.h"

/**
 * _strlen - hello
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
	int j = 0;
	int k = 0;
	int l;

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
