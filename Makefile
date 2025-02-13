CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3 -I./defined_functions
# I_FLAGS += $(shell pkg-config --cflags gtk4) # include flags
# L_FLAGS += $(shell pkg-config --libs gtk4)   # link flags

CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean 

all:
	${CCMD} *.c defined_functions/*.c -o hsh

clean:
	$(RM) *~ *.exec *.o hsh
