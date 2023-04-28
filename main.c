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
		return (pipedInputCase(argv[0], envp));/*might be wrong return value*/
	return (0);
}
