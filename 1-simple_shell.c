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
	size_t len = 0, wsize = 10;

	copy = strdup(input);
	if (copy == NULL)
	{
		perror("Memory allocation failed"), exit(1);
	}
	len = strlen(copy);
	if (len > 0 && copy[len - 1] == '\n')
		copy[len - 1] = '\0';
	token =  strtok(copy, delim);
	words = malloc(wsize * sizeof(char *));
	if (words == NULL)
		perror("Memory allocation failed"), exit(1);
	while (token != NULL)
	{
		words[count] = strdup(token);
		if (words == NULL)
			perror("Memory allocation failed"), exit(1);
		count++, token = strtok(NULL, delim);
		if (count % wsize == 0)
		{
			size_t nsize = (count / wsize + 1) * wsize;
			words = realloc(words, nsize * sizeof(char *));
			if (words == NULL)
				perror("Memory allocation failed"), exit(1);
		}
	}
	free(copy);
	words = realloc(words, (count + 1) * sizeof(char *));
	if (words == NULL)
		perror("Memory allocation failed"), exit(1);
	words[count] = NULL;
	return (words);
}
/**
 * _getline - will get a str entered by user and save it to a buffer
 * @buff: str entered
 * @n: ptr to num of bytes
 * @stream: stream type
 * Return: buff me location
 */


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
		fprintf(stderr, "%s: %s: not found\n", argv[0], argv[0]);
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
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			perror(argv[0]);
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
