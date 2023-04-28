#ifndef SIMPLE_SHELL_FUNCTIONS_H
#define SIMPLE_SHELL_FUNCTIONS_H
void printenv(char *envp[]);
void SignalHandler(int sig);
int systemCallWrapper(char *nextArgv[], char *b, char *envp[]);
#endif
