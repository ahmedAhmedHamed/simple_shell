#include "main.h"

/**
 * et3amel - handles special case of input being piped into program
 * @argv: ...
 * Return: 1 if forked, 0 else.
 */
int et3amel(char *argv[])
{
	int processID;
	struct stat istat;
	char *argv2[1] = {0};

	if (stat(argv[1], &istat))/*checking if file exists*/
	{/*error message likely needs to be changed*/
		write(STDERR_FILENO, "No such file or directory\n", 26);
		return (0);
	}

	processID = fork();
	if (!processID)/*evaluates to true in fork's child*/
	{
		execve(argv[0], argv2, environ);
		perror("execve");
		return (1);
	}
	return (1);
}

/**
 * main - simple shell
 * @argc: ...
 * @argv: ...
 * Return: exit code
 */
int main(int argc, char *argv[])
{
	int waitID = argc;
	char *b = NULL;/*necessary for usage with getline*/
	size_t characters;
	int processID;
	struct stat istat;
	char *_argv[10];/*TODO change if too low*/
	if (argv[1])
	{
		processID = fork();
		wait(&waitID);
		if (!processID)
		{
			et3amel(argv);
			frees(_argv);
			return (-1);
		}
	}
	while (true)
	{
		characters = setupInput(_argv, &b);
		if (feof(stdin)) /*checking for end of file*/
		{
			frees(_argv);
			return (0);
		}
		formatString(characters, _argv, b);
		if (isEqual(_argv[0], "exit"))
		{
			if (_argv[1] != NULL)
			{
				frees(_argv);
				return (atoi(_argv[1]));
			}
			else
			{
				frees(_argv);
				return (0);
			}
		}
		if (checkFunctions(_argv))
		{
			frees(_argv);
			continue;
		}
		if (stat(_argv[0], &istat))/*checking if file exists*/
		{/*error message likely needs to be changed*/
			write(1, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			frees(_argv);
			continue;
		}
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(_argv[0], _argv, environ);
			perror("execve");
			return (0);
		}
		frees(_argv);
		wait(&waitID);
	}
}
