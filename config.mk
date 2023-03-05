# configuration of system

# installation
PREFIX ?= /usr/local
MANPREFIX = ${PREFIX}/share/man


# Note put version before including

CC       = gcc
INC     += -I. -I./include -I/usr/include
CFLAGS  += -W -Wall -Werror -std=c99 -pedantic -Wno-unused-result ${INC}
CPPFLAGS =\
	-DVERSION=\"${VERSION}\"\
	-D_BSD_SOURCE\
	-D_DEFAULT_SOURCE\
	-D_POSIX_C_SOURCE=200809L
OUTPUT_OPTION = -MMD -MP
LDFLAGS =


# archive static library
%.a:
	ar rcs $@ $^
