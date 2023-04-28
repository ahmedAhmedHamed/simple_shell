#ifndef SIMPLE_SHELL_PATHHANDLING_H
#define SIMPLE_SHELL_PATHHANDLING_H
char *findEnv(char *search);
char *myStrDup(char *toDupe);
void myStrCat(char *dest, char *src);
char *get_location(char *command);
#endif
