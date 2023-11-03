#ifndef MISC_H
#define MISC_H
#include <errno.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *s_concat(char *, char *);

void get_adsolute_path(char *, char *);

char *make_string(const char *);

void path_join(char *dest, ...);

void path_name(char *);

int path_create(char *, mode_t);

#endif // !misc
