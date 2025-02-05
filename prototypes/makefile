CC = gcc

UTILS = util_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean


all: pid ppid noargc readline splitter execve forker wait five stat envmain $\
	environ which simpsh which env-utils getenv setenv unsetenv

pid:
	${CCMD} pid.c -o pid.exec

ppid:
	${CCMD} ppid.c -o ppid.exec

noargc:
	${CCMD} noargc.c -o noargc.exec

readline:
	${CCMD} readline.c -o readline.exec

splitter:
	${CCMD} splitter.c -o splitter.exec

execve:
	${CCMD} execve.c -o execve.exec

forker:
	${CCMD} forker.c -o forker.exec

wait:
	${CCMD} wait.c -o wait.exec

five:
	${CCMD} exec5.c -o exec5.exec

stat:
	${CCMD} stat.c -o stat.exec

envmain:
	${CCMD} envmain.c -o envmain.exec

environ:
	${CCMD} environ.c -o environ.exec

which:
	${CCMD} _which.c ${UTILS} -o _which.exec

env-utils:
	${CCMD} test/env-utils.test.c chepe-str.c -o env-utils.exec

getenv:
	${CCMD} test/_getenv.test.c env_utils.c chepe-str.c -o _getenv.exec

setenv:
	${CCMD} test/_setenv.test.c ${UTILS} -o _setenv.exec

unsetenv:
	${CCMD} test/_unsetenv.test.c ${UTILS} -o _unsetenv.exec

simpsh:
	${CCMD} simpsh.c ${UTILS} -o simpsh.exec

clean:
	$(RM) *~ *.exec *.o
