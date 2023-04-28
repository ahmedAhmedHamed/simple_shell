#include "main.h"

/**
 * printenv - prints everything that's inside the environ variable
 * @envp: ...
 */
void printenv(char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		write(STDOUT_FILENO, envp[i], _strlen(envp[i]));
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
 * @nextArgv: ...
 * @b: ...
 * @envp: ...
 * Return: 1 if it calls something 0 if it doesn't
 */
int systemCallWrapper(char *nextArgv[], char *b, char *envp[])
{
	if (isEqual(nextArgv[0], "env"))
	{
		printenv(envp);
		frees(nextArgv);
		free(b);
		b = NULL;
		return (1);
	}
	return (0);
}

/**
 * EXIT - handles the exit call
 * @nextArgv: ...
 * @b: ...
 * @progName: ...
 * @waitID: ...
 */
void EXIT(char *nextArgv[], char *b, char *progName, int waitID)
{
	int exit_status;

	free(b);
	if (nextArgv[1] != NULL)
	{
		exit_status = ouratoi(nextArgv[1]);
		if (exit_status != -7)
		{
			frees(nextArgv);
			exit(exit_status);
		}
		write(STDERR_FILENO, progName, _strlen(progName));
		write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
		write(STDERR_FILENO, nextArgv[1], _strlen(nextArgv[1]));
		write(STDERR_FILENO, "\n", 1);
		frees(nextArgv);
		exit(2);
	}
	if (WIFEXITED(waitID))
	{
		frees(nextArgv);
		exit_status = WEXITSTATUS(waitID);
		exit(exit_status);
	}
	frees(nextArgv);
	exit(0);
}
