#ifndef SIMPLE_SHELL_CASEPIPE_H
#define SIMPLE_SHELL_CASEPIPE_H
int handlePipeInput(char *argv[], char *envp[], char *progName);
int pipedInputCase(char *progName, char *envp[]);
void freeChpointer(char **freedom);
#endif
