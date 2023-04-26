#include "main.h"

/**
 * main - simple shell
 * Return: exit code
 */
int main(void)
{
	int waitID;
	char buffer[BUFSIZE];
	char *b = buffer;/*necessary for usage with getline*/
	size_t bufSize = BUFSIZE;
	size_t characters;
	int processID;
	struct stat istat;
	char *argv[10];/*TODO change if too low*/
	int i;

	while (true)
	{
		characters = setupInput(argv, b);
		if (feof(stdin)) /*checking for end of file*/
			return (0);
		formatString(characters, argv, b);
		if (!strcmp(argv[0], "exit"))
		{
			if (argv[1] != NULL)
				return (atoi(argv[1]));
			else
				return (0);
		}
		if (checkFunctions(argv))
			continue;
		if (stat(argv[0], &istat))/*checking if file exists*/
		{
			fprintf(stderr, "No such file or directory\n");
			continue;
		}
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(argv[0], argv, environ);
			perror("execve");
			return (0);
		}
		wait(&waitID);
	}
}
