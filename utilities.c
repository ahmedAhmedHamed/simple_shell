#include "main.h"

/**
 * isEqual - checks if two strings are equal(returns 1 if they are equal)
 * @one: ...
 * @two: ...
 * Return: one on equality, 0 on inequality.
 */
int isEqual(char *one, char *two)
{
	while (*one)
	{
		if (*one != *two)
			return (0);
		one++;
		two++;
	}
	return (1);
}


/**
 * frees - frees _argv
 * @_argv: Array to be freed
 */
void frees(char *_argv[10])
{
	int i = 0;

	while (_argv != NULL && _argv[i] != NULL)
	{
		free(_argv[i]);
		_argv[i] = NULL;
		i++;
	}
}

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
 * strtoking - separates b into nextArgv using a space as a delimiter
 * @nextArgv: ...
 * @b: ...
 */
void strtoking(char *nextArgv[10], char *b)
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
		nextArgv[k] = malloc(sizeof(char) * ((i - j) + 1));
		while (i != j)
		{
			nextArgv[k][l] = b[j];
			j++;
			l++;
		}
		nextArgv[k][l] = '\0';
		printf("X%sX\n", nextArgv[k]);
		dumpWhitespace(&(nextArgv[k]));
		printf("X%sX\n", nextArgv[k]);
		k++;
		i++;
		j = i;
	}
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
