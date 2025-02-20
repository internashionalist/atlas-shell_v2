#ifndef _builtins_h_
#define _builtins_h_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dec_cd.h"
#include "dec_env.h"
#include "dec_str.h"
#include "dec_exit.h"

int is_builtin(char **input_tokens);
int handle_builtin(char **input_tokens);

#endif /* _builtins_h_ */
