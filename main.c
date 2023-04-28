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
 * myStrCpy - copies from to to using malloc WITHOUT any protection
 * @from: string to be copied
 * @to: string to be copied to
 */
void myStrCpy(char *from, char **to)
{
	int i = 0;
	int stop = _strlen(from);
	(*to) = malloc(_strlen(from) * sizeof(char));

	while (i <= stop)
	{
		(*to)[i] = from[i];
		i++;
	}
}

/**
 *
 */
void handlePipeInput(char *argv[], char *envp[])
{
	int processID;
	struct stat istat;

	processID = fork();
	if (!processID)/*evaluates to true in fork's child*/
	{
		if (stat(argv[0], &istat))/*checking if file exists*/
		{/*error message likely needs to be changed*/
			write(1, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			return;
		}
		execve(argv[0], argv, envp);
		perror("execve");
	}
	wait(&processID);
}

/**
 * argv - ...
 * @argv: ...
 * Return: ...
 */
int pipedInputCase(char *envp[])
{
	int characters;
	int waitID;
	int i = 4;
	char *b = NULL;/*necessary for usage with getline*/
	char *nextArgv[10];

	while (i--)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		if (characters == -1)
			return (0);
		formatString(characters, nextArgv, b);
		handlePipeInput(nextArgv, envp);

		wait(&waitID);
		frees(nextArgv);
		free(b);
		b = NULL;

	}
	return (0);
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
	char *nextArgv[10];
	(void) argc;
	(void) argv;

	if (!isatty(STDIN_FILENO))
		return (pipedInputCase(envp));/*might be wrong return value*/

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
			continue;
		}

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
