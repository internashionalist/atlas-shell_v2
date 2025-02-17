#include "util_str.h"
#include "util_path.h"
#include "util_env.h"
#include <stdio.h>
#include <stdlib.h>

/******** PATH CHAIN ********/

/* comment out section if unneeded */

linked_path *init_path_chain()
{
	linked_path
		*head = malloc(sizeof(linked_path)),
		*prev = head,
		*next = NULL;
	char *path = navigate_path();

	head->path = _strdup(path);
	head->prev = NULL;
	head->next = NULL;
	prev = head;

	while ((path = navigate_path()))
	{
		next = malloc(sizeof(linked_path));
		next->path = _strdup(path);
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
