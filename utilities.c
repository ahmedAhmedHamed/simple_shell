#include "main.h"

/**
 * isEqual - checks if two strings are equal(returns 1 if they are equal)
 * @one: ...
 * @two: ...
 * Return: one on equality, 0 on inequality.
 */
int isEqual(char *one, char *two)
{
	if (one == NULL || two == NULL)
		return (0);
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
 * dumpWhitespace - removes the whitespace from a string
 * @toBeTrimmed: ...
 * Return: 1 always
 */
int dumpWhitespace(char *toBeTrimmed)
{
	int  i;
	int j;

	for (i = 0; toBeTrimmed[i] == ' '; i++)
		;

	for (j = 0; toBeTrimmed[i]; i++)
		toBeTrimmed[j++] = toBeTrimmed[i];
	toBeTrimmed[j] = '\0';
	for (i = 0; toBeTrimmed[i] != '\0'; i++)
		if (toBeTrimmed[i] != ' ')
			j = i;
	toBeTrimmed[j + 1] = '\0';
	return (1);
}

/**
 * ouratoi - string to integer
 * @s: string to get int out of
 * Return: the number on success, minus 7 on failure or if num has a char.
 */
int ouratoi(char *s)
{
	int number = 0;
	int i;

	if (s == NULL)
		return (-7);
	for (i = 0; i < _strlen(s); i++)
	{
		if (!(s[i] > 47 && s[i] < 58))
			return (-7);
		number = number * 10 + (s[i] - 48);
	}
	return (number);
}
