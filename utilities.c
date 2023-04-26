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