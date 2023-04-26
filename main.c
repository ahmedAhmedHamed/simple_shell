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

int et3amel(char *argv[])
{
	struct stat istat;
	char *argv2[1] = {0};
	if (stat(argv[1], &istat))/*checking if file exists*/
	{/*error message likely needs to be changed*/
		fprintf(stderr, "No such file or directory\n");
		return (0);
	}

	execve(argv[1], argv2, environ);
	perror("execve");
	return (1);
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
	if (argv[1])
	{
		processID = fork();
		wait(&waitID);
		if (!processID)
		{
			et3amel(argv);
			return (-1);
		}
	}
	while (true)
	{
		characters = setupInput(_argv, b);
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
		{/*error message likely needs to be changed*/
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
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
