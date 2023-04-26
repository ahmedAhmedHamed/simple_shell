#include "main.h"

void move_argv_into__argv(char *argv[], char *_argv[10])
{
	int i = 0;
	while (argv[i] != 0)
	{
		_argv[i] = argv[i];
		i++;
	}
}

/**
 * main - simple shell
 * Return: exit code
 */
int main(int argc, char *argv[])
{
	int waitID;
	char buffer[BUFSIZE];
	char *b = buffer;/*necessary for usage with getline*/
	size_t characters = argc;
	int processID;
	struct stat istat;
	char *_argv[10];/*TODO change if too low*/

	while (true)
	{
		characters = setupInput(_argv, b);
		move_argv_into__argv(argv, _argv);
		if (feof(stdin)) /*checking for end of file*/
			return (0);
		formatString(characters, _argv, b);
		if (!strcmp(_argv[0], "exit"))
		{
			if (_argv[1] != NULL)
				return (atoi(_argv[1]));
			else
				return (0);
		}
		if (checkFunctions(_argv))
			continue;
		if (stat(_argv[0], &istat))/*checking if file exists*/
		{
			fprintf(stderr, "No such file or directory\n");
			continue;
		}
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(_argv[0], _argv, environ);
			perror("execve");
			return (0);
		}
		wait(&waitID);
	}
}
