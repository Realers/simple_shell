#include "shell.h"
/**
 * main - will run an instance of simple_shell
 * Return: 0 on success.
 */
int main(void)
{
	char *cmd = NULL, *path, *cpath;
	size_t len = 0;
	ssize_t line = 0;
	char **argv;
	Node *head = '\0';

	while (line != EOF)
	{
		is_interactive();
		line = getline(&cmd, &len, stdin);
		argv = _splitstr(cmd);
		if (strcmp(cmd, "exit\n") == 0)
		{
			break;
		}
		else
		{
			path = getenv("PATH"), head = join_paths(path);
			cpath = _pathFilename(argv[0], head);
			if (!cpath && argv != NULL)
			{
				_runline(argv);
			}
			else
			{
				free(argv[0]), argv[0] = cpath;
				_runline(argv);
			}
		}
	}
	free(cmd);
	freeargs(argv);
	free_list(head);
	return (0);
}
