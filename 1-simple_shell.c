#include "shell.h"
/**
 * _splitstr - will split str to [] of ptr to words
 * @input: input str
 * Return: Array of ptr
 */
char **_splitstr(char *input)
{
	char **words = NULL;
	int count = 0;
	char *token, *copy, *delim = " \t\n";
	size_t len = 0;

	copy = strdup(input);
	if (copy == NULL)
	{
		perror("Memory allocation failed"), exit(1);
	}
	len = strlen(copy);
	if (len > 0 && copy[len - 1] == '\n')
		copy[len - 1] = '\0';
	token =  strtok(copy, delim);
	while (token != NULL)
	{
		words = realloc(words, (count + 1) * sizeof(char *));
		if (words == NULL)
			perror("Memory allocation failed"), exit(1);
		words[count] = strdup(token);
		if (words[count] == NULL)
			perror("Memory allocation failed"), exit(1);
		count++, token = strtok(NULL, delim);
	}
	words = realloc(words, (count + 1) * sizeof(char *));
	if (words == NULL)
		perror("Memory allocation failed"), exit(1);
	words[count] = NULL;
	free(copy);
	return (words);
}
/**
 * _getline - will get a str entered by user and save it to a buffer
 * @buff: str entered
 * @n: ptr to num of bytes
 * @stream: stream type
 * Return: buff me location
 */
ssize_t _getline(char **buff, size_t *n, FILE *stream)
{
	size_t init_size, final_size, len = 0;
	char *line, *new_line;
	int ch;

	if (!buff || !n || !stream)
		return (-1);
	init_size = *n, line = *buff;
	if (line == NULL)
	{
		line = malloc(init_size);
		if (line == NULL)
			return (-1);
		*n = init_size;
	}
	while (1)
	{
		ch = fgetc(stream);
		if (ch == EOF || ch == '\n')
		{
			if (len > 0 || (ch == '\n' && init_size > 0))
			{
				line[len] = '\0', *buff = line;
				return (len);
			}
			else if (ch == EOF)
			{
				*buff = NULL;
				return (-1);
			}
		}
		if (len + 1 >= init_size)
		{
			final_size = init_size * 2, new_line = realloc(line, final_size);
			if (new_line == NULL)
				*buff = NULL;
			return (-1);
			line = new_line, *n = final_size;
		} line[len++] = (char)ch;
	}
}

/**
 * _runline - will fork wait and execute cmd
 * @argv: argument vectors.
 */
void _runline(char **argv)
{
	pid_t child;
	int status;
	char **env = environ;

	if (!argv)
	{
		return;
	}
	if (!checkCmdValidity(argv))
	{
		perror(argv[0]);
		_nonIntExit();
		return;
	}
	child = fork();
	if (child == -1)
	{
		exit(1);
	}
	else if (child == 0)
	{
		execve(argv[0], argv, env);
		perror(argv[0]);
		exit(1);
	}
	else
	{
		waitpid(child, &status, 0);
		_nonIntExit();
	}
}
/**
 * freeargs - frees the array of pointers args
 * @args: array of pointers
 */

void freeargs(char **args)
{
	int x;

	if (args != NULL)
	{
		for (x = 0; args[x]; x++)
		{
			free(args[x]);
		}
	}
	free(args);
}

/**
 * is_interactive - will check if interactive / non-interactive.
 */
void is_interactive(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("%s", "#cisfun$ ");
		fflush(stdout);
	}
}
