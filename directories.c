#include "shell.h"
/**
 * append_dir - will add dir to linked list
 * @head: ptr to list head
 * @dir: directory
 * Return: ptr to newly added item
 */
Node *append_dir(Node *head, char *dir)
{
	Node *_node = malloc(sizeof(Node));

	if (_node == NULL)
	{
		printf("Error\n");
		exit(1);
	}

	_node->dir = strdup(dir);

	if (_node->dir == NULL)
	{
		free(_node);
		exit(1);
	}
	_node->next = head;
	return (_node);
}
/**
 * free_list - frees list of directories in memory
 * @head: ptr to head of list
 */
void free_list(Node *head)
{
	Node *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->dir);
		free(tmp);
	}
}
/**
 * join_paths - will join path str to linked list of Path names
 * @path: PATH str
 * Return: linked list of path Nodes.
 */

Node *join_paths(char *path)
{
	Node *head = NULL;
	char *token;
	char *cpath = strdup(path);

	if (cpath == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	token = strtok(cpath, ":");
	while (token)
	{
		head = append_dir(head, token);
		if (head == NULL)
		{
			fprintf(stderr, "Error\n");
			break;
		}
		token = strtok(NULL, ":");
	}
	free(cpath);
	return (head);
}

/**
 * _pathFilename - finds filename of pathname
 * @filename: fn or cmd
 * @head: linked list of dir
 * Return: str or NULL.
 */

char *_pathFilename(char *filename, Node *head)
{
	struct stat st;
	char *str = NULL;
	Node *temp = head;

	while (temp)
	{
		str = malloc(strlen(temp->dir) + strlen(filename) + 2);
		if (str == NULL)
		{
			return (NULL);
		}
		strcpy(str, temp->dir);
		strcat(str, "/"), strcat(str, filename);
		if (stat(str, &st) == 0)
		{
			return (str);
		}
		temp = temp->next;
		free(str);
	}
	return (NULL);
}
