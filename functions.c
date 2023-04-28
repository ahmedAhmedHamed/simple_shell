#include "main.h"

/**
 * printenv - prints everything that's inside the environ variable
 * @envp: ...
 */
void printenv(char *envp[])
{
	int i;

	(void) envp;
	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * SignalHandler - handles the signal
 * @sig: s
 */
void SignalHandler(int sig)
{
	char *prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, SignalHandler);
	write(STDIN_FILENO, prompt, 3);
}

/**
 * systemCallWrapper - chooses which system call to call, if any
 * this is the same as the checkfunctions function from old commits.
 * @nextArgv: ...
 * @b: ...
 * @envp: ...
 * Return: 1 if it calls something 0 if it doesn't
 */
int systemCallWrapper(char *nextArgv[], char *b, char *envp[])
{
	int returnCode;

	if (isEqual(nextArgv[0], "env"))
		return (sysPrintEnv(nextArgv, b, envp));

	if (isEqual(nextArgv[0], "setenv"))
	{
		(returnCode) = sysSetEnv(nextArgv);
		freeAll(b, nextArgv);
		return (returnCode);
	}

	if (isEqual(nextArgv[0], "unsetenv"))
	{
		(returnCode) = (_unsetenv(nextArgv));
		freeAll(b, nextArgv);
		return (returnCode);
	}

	if (isEqual(nextArgv[0], "cd"))/*likely need to handle $VARIABLE*/
	{
		free(b);
		return (changeDir(nextArgv));
	}

	return (0);
}
