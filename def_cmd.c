#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> /* file mode_t defs */
#include "dec_str.h"
#include "dec_env.h"
#include "dec_path.h"
#include "dec_parser.h"
#include "dec_cmd.h"
#include "dec_builtins.h"
#include "dec_util.h"

#define READ_END  0
#define WRITE_END 1


char **_get_cmd(char *cmd, char **cmdpath)
{
	char **cmd_tokens;

	cmd_tokens = tokenize(cmd, " ", 512);

	if (!cmd_tokens[0])
	{
		*cmdpath = NULL;
		return (cmd_tokens);
	}

	if (cmd_tokens[0][0] == '/' || cmd_tokens[0][0] == '.')
	{
		if (access(cmd_tokens[0], X_OK) == 0)
			*cmdpath = str_dup(cmd_tokens[0]);
		else
			*cmdpath = NULL;
	}

	else
	{
		*cmdpath = _which(cmd_tokens[0]);
	}

	return (cmd_tokens);
}


static int run_external(char *cmdpath, char **cmd_tokens, int fdesc)
{
    pid_t pid;
    int wstatus;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 0;
    }
    if (pid == 0)
    {
        /* child */
        if (fdesc != STDOUT_FILENO)
        {
            dup2(fdesc, STDOUT_FILENO);
            close(fdesc);
        }
        if (cmdpath)
            execve(cmdpath, cmd_tokens, environ);

        /* if exec failed: */
        perror("execve");
        _exit(127);
    }
    else
    {
        /* parent waits */
        wait(&wstatus);
        if (fdesc != STDOUT_FILENO)
            close(fdesc);
    }

    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
        return 1;
    else
        return 0;
}


int _run_cmd(char *cmdpath, char **cmd_tokens, int code, int fdesc)
{
    int wstatus = 0;
    static int readin = STDIN_FILENO; /* for piping */
    int writeout;
    int linker[2];

	if (code == RIN || code == RRIN) /* input redirection */
    {
        if (is_builtin(cmd_tokens[0]))
        {
            int save_in = dup(STDIN_FILENO);
            dup2(fdesc, STDIN_FILENO);
            wstatus = handle_builtin(cmd_tokens);
            dup2(save_in, STDIN_FILENO);
            close(save_in);
        }
        else
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return 0;
            }
            if (pid == 0)
            {
                dup2(fdesc, STDIN_FILENO);
                if (cmdpath)
                    execve(cmdpath, cmd_tokens, environ);
                perror("execve");
                _exit(127);
            }
            else
            {
                wait(&wstatus);
            }
        }
        if (fdesc != STDIN_FILENO)
            close(fdesc);
        return wstatus;
    }

    /* otherwise, handle output redir / piping */
    if (cmd_tokens[0] && is_builtin(cmd_tokens[0]))
    {
        /* 
         * For piping: if code == BAR, we need a pipe for next command's input.
         */
        pipe(linker);
        if (fdesc != STDOUT_FILENO)
            writeout = fdesc;
        else if (code == BAR)
            writeout = linker[WRITE_END];
        else
            writeout = STDOUT_FILENO;

        /* set up redirection in the parent */
        int save_out = dup(STDOUT_FILENO);
        if (writeout != STDOUT_FILENO)
        {
            dup2(writeout, STDOUT_FILENO);
            close(writeout);
        }
        if (readin != STDIN_FILENO)
        {
            dup2(readin, STDIN_FILENO);
            close(readin);
        }

        /* run built-in in the parent */
        wstatus = handle_builtin(cmd_tokens); /* e.g. 1=success,0=fail */

        /* restore stdout, close pipe if any */
        dup2(save_out, STDOUT_FILENO);
        close(save_out);

        if (code == BAR)
            readin = linker[READ_END];
        else
            readin = STDIN_FILENO;
    }
    else
    {
        /* external command path */
        pipe(linker);
        if (fdesc != STDOUT_FILENO)
            writeout = fdesc;
        else if (code == BAR)
            writeout = linker[WRITE_END];
        else
            writeout = STDOUT_FILENO;

        /* run external in child process */
        wstatus = run_external(cmdpath, cmd_tokens, writeout);

        if (readin != STDIN_FILENO)
            close(readin);
        if (code == BAR)
            readin = linker[READ_END];
        else
            readin = STDIN_FILENO;
    }

    return wstatus;
}


int _redir_left(char *filename, int append)
{
    int fdesc;
    int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    int fflags = O_CREAT | O_WRONLY | append;

    fdesc = open(filename, fflags, fmode);

    dup2(fdesc, STDOUT_FILENO);

    return fdesc;
}


int _redir_left_input(char *filename)
{
    int fdesc;
    char *input = NULL;
    size_t len = 0;

    if (filename == NULL || str_len(filename) == 0)
        return -1;

    fdesc = open("/tmp/heredoc_temp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdesc < 0)
        return -1;

    while (getline(&input, &len, stdin) != -1)
    {
        if (_strcmp(input, filename) == 0)
            break;

        write(fdesc, input, strlen(input));
    }

    free(input);

    close(fdesc);

    fdesc = open("/tmp/heredoc_temp_file", O_RDONLY);
    if (fdesc < 0)
        return -1;

    return fdesc;
}


int _setup_redir(char *filename, int fdesc, int code)
{
	if ((code == LOUT || code == LLOUT) && fdesc != STDOUT_FILENO)
		close(fdesc);
	if ((code == RIN  || code == RRIN) && fdesc != STDIN_FILENO)
		close(fdesc);

	filename = str_strip(filename);

	switch (code)
	{
	case (LOUT):
		fdesc = _redir_left(filename, 0);
		break;
	case (LLOUT):
		fdesc = _redir_left(filename, O_APPEND);
		break;
	case (RIN):
		fdesc = _redir_left_input(filename);
		break;
	/* case (RRIN):
		fdesc = heredoc function
		break; */
	default:
		fdesc = -1;
	}

	free(filename);

	return (fdesc);
}


int _resolve_logic(int cmdexit, int operand)
{
	switch (operand)
	{
	    case (BBAR):
		    if (cmdexit == 0)
			    return (1);
		    break;
	    case (AAND):
		    if (cmdexit == 1)
			    return (1);
		    break;
	}
	return (0);
}


int proc_cmds(char *line)
{
	char *separ, *filename = NULL, *cmd, **cmd_tokens, *cmdpath;
	int sep, red, fdesc = -1, cmdexit, skip = 0;

	line = str_strip(line);

	while ((separ = get_separation(line, &sep)))
	{
		fdesc = STDOUT_FILENO;
		separ = str_dup(separ);
		cmd = get_redirection(separ, &red);
		cmd = str_dup(cmd);

		filename = get_redirection(separ, &red);
        while (filename != NULL)
        {
            fdesc = _setup_redir(filename, fdesc, red);
            filename = get_redirection(separ, &red);
        }

		cmd_tokens = _get_cmd(cmd, &cmdpath);

		if (!skip)
		{
			if (cmd_tokens[0] && !is_builtin(cmd_tokens[0]) &&
				cmdpath == NULL)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_tokens[0]);
				cmdexit = 0;
			}
			else
			{
				cmdexit = _run_cmd(cmdpath, cmd_tokens, sep, fdesc);
			}
		}

        skip = _resolve_logic(cmdexit, sep);

		free(cmd);
		free(cmdpath);
		free(cmd_tokens);
		free(separ);
	}

	free(line);

	return (0);
}
