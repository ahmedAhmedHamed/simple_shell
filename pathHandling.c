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
						if (environ[i][4] == '=')
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
	char *duplicated = malloc(_strlen(toDupe) * sizeof(char));
	int i = 0;

	while (toDupe[i] != '\0')
	{
		duplicated[i] = toDupe[i];
		i++;
	}
	duplicated[i] = toDupe[i];
	return (duplicated);
}

/**
 * myStrCat - concatenates two strings
 * @dest: destination string
 * @src: source string
 */
void myStrCat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
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

	if (path){
		/* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/
		pathCopy = myStrDup(path);
		/* Get length of the command that was passed */
		commandLength = _strlen(command);
		/* Let's break down the path variable and get all the directories available*/
		pathToken = strtok(pathCopy, ":");/*strtok usage :(*/
		while(pathToken != NULL){
			/* Get the length of the directory*/
			directory_length = _strlen(pathToken);
			/* allocate memory for storing the command name together with the directory name */
			filePath = malloc(commandLength + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
			/* to build the path for the command, let's copy the directory path and concatenate the command to it */
			myStrCpy(pathToken, &filePath);
			strcat(filePath, "/");
			strcat(filePath, command);
			strcat(filePath, "\0");
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
