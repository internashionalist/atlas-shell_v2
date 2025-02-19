CC = gcc

MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
UTILS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean


all: pid ppid noargc readline splitter execve forker wait five stat envmain $\
	environ which simpsh which env-utils getenv setenv unsetenv

interpreter:
	clear
	${CCMD} ${UTILS} interpretor.test.c -o interpreter.exec
	${MEMTEST} ./interpreter.exec ./dummy_logic.sh

prepipe:
	${CCMD} pipe-pre.c -o prepipe.exec

postpipe:
	${CCMD} pipe-post.c -o postpipe.exec

pipe-stack:
	${CCMD} pipe-stacking.c -o stacker.exec

piper:
	${CCMD} piper.c ${UTILS} -o piper.exec

lsrev:
	${CCMD} pipe-lsrev.c -o lsrev.exec

lsrevwc:
	${CCMD} pipe-lsrevwc.c -o lsrevwc.exec

pipe-echo:
	${CCMD} pipe-echo.exr.c -o pipe-echo.exec

redir-input:
	${CCMD} redir-input.exr.c -o redir-input.exec

redir-file:
	${CCMD} redir-file.exr.c -o redir-file.exec

redir-append:
	${CCMD} redir-append.exr.c -o redir-append.exec

pid:
	${CCMD} pid.exr.c -o pid.exec

ppid:
	${CCMD} ppid.exr.c -o ppid.exec

noargc:
	${CCMD} noargc.exr.c -o noargc.exec

readline:
	${CCMD} readline.exr.c -o readline.exec

splitter:
	${CCMD} splitter.exr.c -o splitter.exec

execve:
	${CCMD} execve.exr.c -o execve.exec

forker:
	${CCMD} forker.exr.c -o forker.exec

wait:
	${CCMD} wait.exr.c -o wait.exec

five:
	${CCMD} exec5.exr.c -o exec5.exec

stat:
	${CCMD} stat.exr.c -o stat.exec

envmain:
	${CCMD} envmain.exr.c -o envmain.exec

environ:
	${CCMD} environ.exr.c -o environ.exec

which:
	${CCMD} _which.c ${UTILS} -o _which.exec

env-utils:
	${CCMD} test/env-utils.test.c ${UTILS} -o env-utils.exec

getenv:
	${CCMD} test/_getenv.test.c ${UTILS} -o _getenv.exec

setenv:
	${CCMD} test/_setenv.test.c ${UTILS} -o _setenv.exec

unsetenv:
	${CCMD} test/_unsetenv.test.c ${UTILS} -o _unsetenv.exec

simpsh:
	${CCMD} simpsh.c ${UTILS} -o simpsh.exec

clean:
	$(RM) *~ *.exec *.o *.out
