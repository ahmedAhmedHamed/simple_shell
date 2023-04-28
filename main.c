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
 * argv - ...
 * @argv: ...
 * Return: ...
 */
int pipedInputCase(char *argv[], char *envp[])
{
	int processID;
	struct stat istat;
	char *pipedNextArgv[2] = {0 , 0};
	int i = 0;
	printf("%s ss\n", argv[1]);
	while (argv[i] != NULL)
	{
		processID = fork();
		if (!processID)/*evaluates to true in fork's child*/
		{
			if (stat(argv[i], &istat))/*checking if file exists*/
			{/*error message likely needs to be changed*/
				write(1, argv[i], _strlen(argv[i]));
				write(STDERR_FILENO, ": No such file or directorya7a\n", 28);
				continue;
			}
			myStrCpy(argv[i], &pipedNextArgv[0]);
			printf("\n%s, %d\n", pipedNextArgv[0], i);
			execve(argv[i], pipedNextArgv, envp);
			perror("execve");
		}
		wait(&processID);
		free(pipedNextArgv[0]);
		pipedNextArgv[0] = NULL;
		i++;
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

	myStrCpy(argv[0], &nextArgv[0]);

	while (true)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		formatString(characters, nextArgv, b);
		return (pipedInputCase(nextArgv, envp));
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
			return (pipedInputCase(nextArgv, envp));/*might be wrong return value*/

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
