#include <stdlib.h>
#include "util_path.h"
#include "util_str.h"
#include "util_env.h"
#include "util_which.h"

int main(int count, char **args)
{
	char *pathvar, **paths;
	int err = 0;

	if (count < 2)
		return (1);

	pathvar = _getenv("PATH");
	paths = tokenize(pathvar, "=:", 64);

	for (int a = 1; a < count; a++)
		if (analyze_paths(paths, args[a]) < 0)
			err = 1;

	free(paths);

	return (err);
}
