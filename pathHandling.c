#include "main.h"

/**
 * findEnv - checks for the path environment
 * @search: unused currently
 * Return: the pointer to the entry of the path environment, or null
 */
char *findEnv(char *search)
{
	int i;
	(void) search;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (environ[i][0] == 'P')
		if (environ[i][1] == 'A')
		if (environ[i][2] == 'T')
		if (environ[i][3] == 'H')
			return (environ[i]);
	}

	return (NULL);
}

/**
 * myStrDup - allocates dynamic memory and copies the strings
 * @toDupe: string to be duplicated
 * Return: dynamically allocated string
 */
char *myStrDup(char *toDupe)
{
	char *duplicated = malloc(_strlen(toDupe) * sizeof(char) + 1);
	int i = 0;

	while (toDupe[i] != '\0')
	{
		duplicated[i] = toDupe[i];
		i++;
	}
	duplicated[i] = '\0';
	return (duplicated);
}

/**
 * my_strcat - concatenates strings
 * @destination: ...
 * @source: ...
 * Return: new string
 */
char *my_strcat(char *destination, const char *source)
{
	char *ptr = destination + strlen(destination);

	while (*source != '\0')
		*ptr++ = *source++;

	*ptr = '\0';
	return (destination);
}

/**
 * get_location - gets the location of the command in the path environment var
 * @command: command to be found
 * Return: null if the command doesn't exist, the path to the command otherwise
 */
char *get_location(char *command)
{
	char *path, *pathCopy, *pathToken, *filePath;
	int commandLength, directory_length;
	struct stat buffer;

	path = findEnv("PATH");

	if (path)
	{
		pathCopy = myStrDup(path);
		commandLength = _strlen(command);
		pathToken = strtok(pathCopy, ":");/*strtok usage :(*/
		while (pathToken != NULL)
		{
			directory_length = _strlen(pathToken);
			filePath = malloc(commandLength + directory_length + 2);
			myStrCpy(pathToken, &filePath);
			my_strcat(filePath, "/");
			my_strcat(filePath, command);
			my_strcat(filePath, "\0");
			if (stat(filePath, &buffer) == 0)
			{
				free(pathCopy);
				return (filePath);
			}
			else
			{
				free(filePath);
				pathToken = strtok(NULL, ":");
			}
		}
		free(pathCopy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
