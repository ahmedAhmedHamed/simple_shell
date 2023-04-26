#ifndef SIMPLE_SHELL_MAIN_H
#define SIMPLE_SHELL_MAIN_H
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;
#define BUFSIZE 1024
void _unsetenv(char *argv[10]);
int _strlen(const char *s);
void _setenv(char *argv[10]);
void strtoking(char *argv[10], char *b);
void printenv(void);
void changeDir(char *argv[10]);
int checkFunctions(char *argv[10]);
void formatString(int characters, char *argv[10], char *b);
int setupInput(char **b);
int isEqual(char *one, char *two);
void frees(char *argv[10]);
#endif
