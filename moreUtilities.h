#ifndef SIMPLE_SHELL_MOREUTILITIES_H
#define SIMPLE_SHELL_MOREUTILITIES_H
void myStrCpy(char *from, char **to);
int fileExists(char *nextArgv[10]);
void freeAll(char *b, char *nextArgv[]);
void freeExit(char *b, char *nextArgv[]);
#endif
