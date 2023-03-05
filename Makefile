# See LICENSE for details
# makefile for sample

.PHONY: all clean dist install uninstall
.DEFAULT: all

VERSION = 1.0
LIBSAMPLE_DIR = ./libsample
LIBSAMPLE = ${LIBSAMPLE_DIR}/libsample.a
INC = -I${LIBSAMPLE_DIR}/include

include config.mk


# Files for distribution
PKGFILES = \
	LICENSE\
	Makefile\
	README.md\
	cli.c\
	config.def.h\
	config.mk\
	doc\
	include\
	libsample\
	man\
	sample.c\
	util.c

SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
BIN = sample


all: config.h ${BIN}
	@echo "sample built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN} *.tar.gz
	@make -C ${LIBSAMPLE_DIR} clean


options:
	@echo "sample compilation flags"
	@echo "CC        = ${CC}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "OUTPUT_OPTION = ${OUTPUT_OPTION}"
	@echo "LDFLAGS   = ${LDFLAGS}"


dist: clean
	mkdir -p sample-${VERSION}
	cp -r ${PKGFILES} sample-${VERSION}
	tar -cz  -f sample-${VERSION}.tar.gz sample-${VERSION}
	rm -r sample-${VERSION}


install: sample
	@echo installing executable file to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f ${BIN} ${PREFIX}/bin
	@chmod 755 ${PREFIX}/bin/sample


uninstall:
	@echo removing executable file from ${PREFIX}/bin
	@rm -f ${PREFIX}/bin/sample


config.h: config.def.h
	cp config.def.h config.h


${LIBSAMPLE}:
	make -C ${LIBSAMPLE_DIR}


sample: config.h ${OBJ} ${LIBSAMPLE}
	${CC} $^ -o $@ ${LDFLAGS}

-include ${DEP}
