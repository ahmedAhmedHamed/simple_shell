#include "main.h"

/**
 * freeChpointer - frees a char pointer
 * @freedom: ...
 */
void freeChpointer(char **freedom)
{
	if (*freedom != NULL)
		free(*freedom);
	*freedom = NULL;
}

/**
 * hasSlash - checks if a string has a slash in it
 * @target: string to be checked
 * Return: 1 if it has a slash, 0 otherwise
 */
int hasSlash(char *target)
{
	int i = 0;

	if (target == 0)
		return (0);
	while (target[i] != '\0')
	{
		if (target[i] == '/')
			return (1);
		i++;
	}

	return (0);
}

/**
 * handlePipeInput - handles input from pipe
 * @argv: ...
 * @envp: ...
 * @progName: ...
 * Return: the process ID of the previous process
 */
int handlePipeInput(char *argv[], char *envp[], char *progName)
{
	int processID = 0;
	struct stat istat;
	char *location = NULL;

	if (!(hasSlash(argv[0])))
	{
		location = get_location(argv[0]);
		if (location == NULL)
		{
			write(STDERR_FILENO, progName, _strlen(progName));
			write(STDERR_FILENO, ": 1:", 4);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			return (0);
		}
		freeChpointer(&argv[0]);
		argv[0] = location;
		location = NULL;
	}

	processID = fork();/*fork must not be called if the command doesn’t exist*/
	if (!processID)/*evaluates to true in fork's child*/
	{
		if (stat(argv[0], &istat))/*checking if file exists*/
		{/*error message likely needs to be changed*/
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			exit(0);
		}
		execve(argv[0], argv, envp);
		perror("execve");
	}
	wait(&processID);
	return (processID);
}

/**
 * pipedInputCase - handles if pipe was input from console
 * @envp: the environment
 * @progName: the name of the caller
 * Return: exit code
 */
int pipedInputCase(char *progName, char *envp[])
{
	int characters;
	int waitID = 0;
	char *b = NULL;/*necessary for usage with myGetline*/
	char *nextArgv[10];

	while (true)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		if (characters == -1)
			freeExit(b, nextArgv);
		formatString(characters, nextArgv, b);

		if (_strlen(nextArgv[0]) == -1)
		{
			freeAll(b, nextArgv);
			continue;
		}

		if (isEqual(nextArgv[0], "exit"))
			EXIT(nextArgv, b, progName, waitID);

		if (systemCallWrapper(nextArgv, b, envp))
			continue;

		waitID = handlePipeInput(nextArgv, envp, progName);
		frees(nextArgv);
		freeChpointer(&b);
	}
	return (0);
}
