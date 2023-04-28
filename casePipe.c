#include "main.h"

/**
 * handlePipeInput - handles input from pipe
 * @argv: ...
 * @envp: ...
 * Return: the process ID of the previous process
 */
int handlePipeInput(char *argv[], char *envp[])
{
	int processID;
	struct stat istat;

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
	char *b = NULL;/*necessary for usage with getline*/
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

		waitID = handlePipeInput(nextArgv, envp);

		frees(nextArgv);
		free(b);
		b = NULL;
	}
	return (0);
}
