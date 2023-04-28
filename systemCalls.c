#include "main.h"

/**
 * sysPrintEnv - prints the environment and frees pointers
 * @nextArgv: to be freed
 * @b: to be freed
 * @envp: the environment
 * Return: always 1
 */
int sysPrintEnv(char *nextArgv[], char *b, char *envp[])
{
	printenv(envp);
	frees(nextArgv);
	free(b);
	b = NULL;
	return (1);
}

/**
 * _unsetenv - unsetenv
 * @argv: argv
 * Return: 1 always
 */
int _unsetenv(char *argv[10])
{
	int errorCatcher;

	errorCatcher = unsetenv(argv[1]);
	if (errorCatcher == -1)
		write(STDERR_FILENO, "unsetenv failed\n", _strlen("unsetenv failed\n"));
	return (1);
}

/**
 * changeDir - does cd
 * @argv: argv
 * Return: 1 always
 */
int changeDir(char *argv[10])
{
	int errorCatcher;

	if (argv[1] == NULL)/*could be wrong, if 1 is null should go home*/
	{
		chdir("/");
		frees(argv);
		return (1);
	}
	if (argv[1][0] == '-' || argv[1][0] == '~')
		argv[1][0] = '/';
	errorCatcher = chdir(argv[1]);
	frees(argv);
	if (errorCatcher == -1)
		write(STDERR_FILENO, "Chdir failed\n", 14);
	return (1);
}

/**
 * _setenv - setenv
 * @argv: hello
 * Return: 1 always
 */
int sysSetEnv(char *argv[10])
{
	int errorCatcher;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		write(STDERR_FILENO, "not enough arguments\n", 21);
		return (1);
	}

	errorCatcher = setenv(argv[1], argv[2], 1);

	if (errorCatcher == -1)
		write(STDERR_FILENO, "setenv failed\n", _strlen("setenv failed\n"));
	return (1);
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