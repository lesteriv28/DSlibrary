#ifndef MYSTRING_H
#define MYSTRING_H
#include <stdio.h>
#include <stdlib.h>
int mystrlen(const char *s);
char *mystrcpy(char *dst, const char *src);
int mystrcmp(const char *s1, const char *s2);
char *mystrdup(const char *src);
#endif