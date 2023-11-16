#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **environ;

/**
 * struct Node - linked list struct for directories
 * @dir: directory
 * @next: ptr to next dir
 */

typedef struct Node
{
	char *dir;
	struct Node *next;
} Node;

Node *append_dir(Node *head, char *dir);

void free_list(Node *head);

char *_getenv(const char *name);

ssize_t _getline(char **buff, size_t *n, FILE *stream);

void _runline(char **argv);

char **_splitstr(char *str);

Node *join_paths(char *path);

char *_pathFilename(char *filename, Node *head);

void freeargs(char **args);

void is_interactive(void);

int checkCmdValidity(char **argv);

void _nonIntExit(void);

#endif
