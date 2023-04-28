#ifndef SIMPLE_SHELL_SYSTEMCALLS_H
#define SIMPLE_SHELL_SYSTEMCALLS_H
int sysSetEnv(char *argv[10]);
int _unsetenv(char *argv[10]);
int changeDir(char *argv[10]);
int sysPrintEnv(char *nextArgv[], char *b, char *envp[]);
void EXIT(char *nextArgv[], char *b, char *progName, int waitID);
#endif
