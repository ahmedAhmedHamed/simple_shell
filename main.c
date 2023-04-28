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
 * ouratoi - string to integer
 * @s: string to get int out of
 * Return: the number on success, minus 7 on failure or if num has a char.
 */
int ouratoi(char *s)
{
	int number = 0;
	int i;

	if (s == NULL)
		return (-7);
	for (i = 0; i < _strlen(s); i++)
	{
		if (!(s[i] > 47 && s[i] < 58))
			return (-7);
		number = number * 10 + (s[i] - 48);
	}
	return (number);
}

/**
 *
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
			exit (0);
		}
		execve(argv[0], argv, envp);
		perror("execve");
	}
	wait(&processID);
	return (processID);
}

/**
 * pipedInputCase - handles if pipe was input from console
 * envp: the environment
 * Return: exit code
 */
int pipedInputCase(char *progName, char *envp[])
{
	int characters;
	int waitID = 0;
	char *b = NULL;/*necessary for usage with getline*/
	char *nextArgv[10];
	int exit_status;

	while (true)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		if (characters == -1)
		{
			frees(nextArgv);
			free(b);
			b = NULL;
			return (0);
		}
		formatString(characters, nextArgv, b);

		if (_strlen(nextArgv[0]) == -1)
		{
			frees(nextArgv);
			free(b);
			b = NULL;
			continue;
		}

		if (isEqual(nextArgv[0], "exit"))
		{
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
				frees(nextArgv);
				exit(2);
			}
			if ( WIFEXITED(waitID) )
			{
				frees(nextArgv);
				exit_status = WEXITSTATUS(waitID);
				exit(exit_status);
			}
			frees(nextArgv);
			exit (0);
		}

		if (isEqual(nextArgv[0], "env"))
		{
			printenv(envp);
			frees(nextArgv);
			free(b);
			b = NULL;
			continue;
		}

		waitID = handlePipeInput(nextArgv, envp);

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

//	if (!isatty(STDIN_FILENO))/*evaluates to true if input is console piped*/
		return (pipedInputCase(argv[0], envp));/*might be wrong return value*/

	while (true)
	{
		signal(SIGINT, SignalHandler);
		characters = setupInput(nextArgv, &b);
		formatString(characters, nextArgv, b);
		if (_strlen(nextArgv[0]) == -1)
		{
			frees(nextArgv);
			free(b);
			b = NULL;
			continue;
		}
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
