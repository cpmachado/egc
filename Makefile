# See LICENSE for details
# makefile for egc

.PHONY: all clean dist install uninstall
.DEFAULT: all

include config.mk

# Files for distribution
PKGFILES = \
	LICENSE\
	Makefile\
	README.md\
	config.mk\
	doc\
	egc.c\
	man

SRC = egc.c
OBJ = ${SRC:.c=.o}
BIN = egc


all: ${BIN}
	@echo "egc built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN} *.tar.gz *.zip

lint:
	cpplint egc.c

options:
	@echo "egc compilation flags"
	@echo "VERSION    = ${VERSION}"
	@echo "CC         = ${CC}"
	@echo "CFLAGS     = ${CFLAGS}"
	@echo "CPPFLAGS   = ${CPPFLAGS}"
	@echo "LDFLAGS    = ${LDFLAGS}"
	@echo "SRC        = ${SRC}"
	@echo "OBJ        = ${OBJ}"
	@echo "BIN        = ${BIN}"


dist: clean
	mkdir -p egc-${VERSION}
	cp -r ${PKGFILES} egc-${VERSION}
	tar -cz  -f egc-${VERSION}.tar.gz egc-${VERSION}
	zip -r egc-${VERSION}.zip egc-${VERSION}
	rm -r egc-${VERSION}

install: egc
	@echo installing executable file to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f ${BIN} ${PREFIX}/bin
	@chmod 755 ${PREFIX}/bin/egc

uninstall:
	@echo removing executable file from ${PREFIX}/bin
	@rm -f ${PREFIX}/bin/egc

${BIN}: ${OBJ}
	${CC} -o $@ $^ ${LDFLAGS}

egc.o: egc.c
egc: ${OBJ}

