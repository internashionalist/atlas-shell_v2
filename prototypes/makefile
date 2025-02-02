CC = gcc

CFLAGS = -Wall -Werror -Wextra -ggdb3
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean 


all: pid ppid noargc readline splitter execve forker wait five simpsh

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

simpsh: 
	${CCMD} simpsh.c -o simpsh.exec 

clean:
	$(RM) *~ *.exec *.o
