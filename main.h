#ifndef SIMPLE_SHELL_MAIN_H
#define SIMPLE_SHELL_MAIN_H
void _unsetenv(char *argv[10]);
void _setenv(char *argv[10]);
void strtoking(char *argv[10], const char *b);
void printenv();
int _strlen(const char *s);
#endif
