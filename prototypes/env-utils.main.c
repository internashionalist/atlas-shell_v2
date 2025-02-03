#include "chepe-str.h"
#include "env-utils.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

char *navigate_path()
{
	static int p = 0;
	static char *pathvar = NULL;
	static char **paths = NULL;

	if (!p)
	{
		/*
		 * strtok destroys the original string and thus, without making a
		 * duplicate, subsequent calls are impossible
		 */
		pathvar = _getenv("PATH");
		pathvar = str_dup(pathvar);
		paths = tokenize(pathvar, "=:", 64);
	}

	p++;
	if (paths[p] != NULL)
		return (paths[p]);
	else
	{
		free(paths);
		free(pathvar);
		pathvar = NULL;
		paths = NULL;
		p = 0;
		return NULL;
	}
}

linked_path *init_path_chain()
{
	linked_path
		*head = malloc(sizeof(linked_path)),
		*prev = head,
		*next = NULL;
	char *path = navigate_path();

	head->path = str_dup(path);
	head->prev = NULL;
	head->next = NULL;
	prev = head;

	while ((path = navigate_path()))
	{
		next = malloc(sizeof(linked_path));
		next->path = str_dup(path);
		next->prev = prev;
		next->next = NULL;

		prev->next = next;
		prev = next;
	}

	return (head);
}


linked_path *nav_path_chain(linked_path *head)
{
	static linked_path *current = NULL;
	linked_path *returner;

	if (head)
		current = head;
	else if (current != NULL)
		current = current->next;

	returner = current;
	return (returner);
}

void erase_path_chain(linked_path *head)
{
	linked_path *next = head, *prev;

	while (next != NULL)
	{
		free(next->prev);
		free(next->path);

		prev = next;
		next = next->next;
	}

	free(prev);
}

void print_paths()
{
	char *path = navigate_path();

	do {
		printf("%s\n", path);
		path = navigate_path();
	} while (path);
}

char *_getenv(const char *name)
{
	int len = 0;

	while (name[len] != '\0')
		len++;

	for (int v = 0; environ[v] != NULL; v++)
		if (str_nmatch(name, environ[v], len))
			return environ[v];

	return (NULL);
}

int comp_addr(void **alpha, void **beta)
{
	printf("%p ?= %p", alpha, beta);

	if (alpha == beta)
		return (0);

	return (-1);
}

void env_environ_are_the_same(char **env)
{
	if (comp_addr((void **) env, (void **) environ) < 0)
		printf(" are not the same\n");
	else
		printf(" are equal\n");
}

/* function tester */
int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	linked_path *head = init_path_chain();
	linked_path *node;

	/* print_paths(); */

	node = nav_path_chain(head);
	do {
		printf("%s\n", node->path);
	} while ((node = nav_path_chain(NULL)));

	erase_path_chain(head);

	return (0);
}
