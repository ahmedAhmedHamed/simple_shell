#include "main.h"

/**
 * setupInput - prints the "$ ", clears argv and takes input into b
 * @_argv: argv
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
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	characters = myGetline(b, &bufSize,  stdin);
	return (characters);
}


/**
 * strtoking - separates b into nextArgv using a space as a delimiter
 * i is where you stop, j is where you end, l is for the new string.
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
		while (b[i] == ' ')
		{
			i++;
			j++;
		}
		if (b[i] == '\0')
			break;

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
		dumpWhitespace(nextArgv[k]);
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
