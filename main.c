#include "main.h"

/**
 * main - hello
 * @argc: ...
 * @argv: ...
 * @envp: ...
 * Return: exit code
 */
int main(int argc, char *argv[], char *envp[])
{
	(void) argc;

//	if (!isatty(STDIN_FILENO))/*evaluates to true if input is console piped*/
		return (pipedInputCase(argv[0], envp));/*might be wrong return value*/
	return (0);
}
