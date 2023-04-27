#include "main.h"

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
 * argv - ...
 * @argv: ...
 * Return: ...
 */
int et3amel(char *argv[], char *envp[])
{
	struct stat istat;
	char *argv2[1] = {0};
	int processID;
	int waitID;

	if (stat(argv[0], &istat))/*checking if file exists*/
	{/*error message likely needs to be changed*/
		write(1, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": No such file or directorya7a\n", 28);
		return (0);
	}
	execve(argv[0], argv2, envp);
	perror("execve");
	return (1);
}

/**
 * main - hello
 * @argc: ...
 * @argv: ...
 * Return: exit code
 */
int main(int argc, char *argv[], char *envp[])
{
	int waitID;
	char *b = NULL;/*necessary for usage with getline*/
	size_t characters;
	int processID;
	int i = 0;
	char *nextArgv[10];
	(void) argc;
	(void) argv;



	while (true)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		formatString(characters, nextArgv, b);
		if (isEqual(nextArgv[0], "exit"))
		{
			frees(nextArgv);
			free(b);
			return (0);
		}
		if (isEqual(nextArgv[0], "env"))
		{
			printenv(envp);
			if (!isatty(STDIN_FILENO))
				return (0);
			continue;
		}
		if (!isatty(STDIN_FILENO))
			return (et3amel(nextArgv, envp));/*might be wrong return value*/

		if (fileExists(nextArgv))
			continue;
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			execve(nextArgv[0], nextArgv, envp);
			perror("execve");
			return (0);
		}
		wait(&waitID);
		frees(nextArgv);
		free(b);
		b = NULL;
		fflush(stdin);
	}
}
