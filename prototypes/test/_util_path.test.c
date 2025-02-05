#include "util_str.h"
#include "util_env.h"
#include "util_path.h"
#include <stdio.h>
#include <stdlib.h>

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
