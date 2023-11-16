#include "shell.h"
/**
 * checkCmdValidity - will check if a command is valid before running shell.
 * @argv: shell command entered.
 * Return: 1 if valid. 0 if invalid.
 */
int checkCmdValidity(char **argv)
{
	const char *builtin[] = {"exit", "env", "setenv", "unsetenv", "cd", "alias"};
	size_t len, x;

	if (argv == NULL || argv[0] == NULL)
	{
		return (0);
	}
	len = sizeof(builtin) / sizeof(builtin[0]);
	for (x = 0; x < len; x++)
	{
		if (strcmp(argv[0], builtin[x]) == 0)
		{
			return (1);
		}
	}
	if (access(argv[0], X_OK) == -1)
	{
		return (0);
	}
	return (1);
}

/**
 * _nonIntExit - will close the program after exercuting cmd if
 * in non-interactive mode.
 */

void _nonIntExit(void)
{
	if (!isatty(STDIN_FILENO))
	{
		exit(0);
	}
}
