#ifndef SIMPLE_SHELL_FUNCTIONS_H
#define SIMPLE_SHELL_FUNCTIONS_H
void printenv(char *envp[]);
void SignalHandler(int sig);
void EXIT(char *nextArgv[], char *b, char *progName, int waitID);
int systemCallWrapper(char *nextArgv[], char *b, char *envp[]);
#endif
