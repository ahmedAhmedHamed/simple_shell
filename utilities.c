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