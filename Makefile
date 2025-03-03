CC = gcc
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)
CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS} ${DB_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean

all: checker

checker:
	${CC} ${CFLAGS} ${DEFS} shell_v2.c -o hsh

test:
	clear
	${CCMD} ${DEFS} shell_v2.c -o sh_v2.x
	${MEMTEST} ./sh_v2.x

clean:
	$(RM) *~ *.exec *.o *.out *.x
