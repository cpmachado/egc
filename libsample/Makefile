# See LICENSE for details

.PHONY: all clean
.DEFAULT: all

include config.mk

SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
BIN = libsample.a


all: ${BIN}
	@echo "${BIN} built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN}


options:
	@echo "libsample compilation flags"
	@echo "CC        = ${CC}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "OUTPUT_OPTION = ${OUTPUT_OPTION}"
	@echo "LDFLAGS   = ${LDFLAGS}"


libsample.a: ${OBJ}


-include ${DEP}
