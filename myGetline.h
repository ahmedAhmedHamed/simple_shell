#ifndef SIMPLE_SHELL_MYGETLINE_H
#define SIMPLE_SHELL_MYGETLINE_H
void *myRealloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assignLineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t myGetline(char **lineptr, size_t *n, FILE *stream);
#endif
