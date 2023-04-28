#ifndef SIMPLE_SHELL_MAIN_H
#define SIMPLE_SHELL_MAIN_H
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
int isEqual(char *one, char *two);
void frees(char *_argv[10]);
int _strlen(const char *s);
void strtoking(char *nextArgv[10], char *b);
int setupInput(char *_argv[10], char **b);
void printenv(char *envp[]);
void formatString(int characters, char *argv[10], char *b);
int fileExists(char *nextArgv[10]);
int pipedInputCase(char *argv[], char *envp[]);
#endif
