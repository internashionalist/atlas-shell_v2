CC = gcc

CFLAGS = -Wall -Werror -Wextra -ggdb3
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean 

pid: 
	${CCMD} pid.c -o pid.exec 

ppid: 
	${CCMD} ppid.c -o ppid.exec 

noargc: 
	${CCMD} noargc.c -o noargc.exec 

prompt: 
	${CCMD} prompt.c -o prompt.exec 

clean:
	$(RM) *~ *.exec *.o
