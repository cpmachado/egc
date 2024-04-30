# See LICENSE for details
# makefile for egc

.PHONY: all clean dist install uninstall
.DEFAULT: all

include config.mk

# Files for distribution
PKGFILES = \
	CHANGELOG.md\
	CODE_OF_CONDUCT.md\
	CONTRIBUTING.md\
	LICENSE\
	Makefile\
	README.md\
	config.mk\
	doc\
	include\
	man\
	src

SRC = ${wildcard src/*.c}
OBJ = ${patsubst src/%.c,obj/%.o, ${SRC}}
BIN = egc


all: ${BIN}
	@echo "egc built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN} *.tar.gz *.zip


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

obj/%.o: src/%.c
	@mkdir -p obj
	${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ $<

${BIN}: ${OBJ}
	${CC} -o $@ $^ ${LDFLAGS}

obj/cli.o: src/cli.c
obj/util.o: src/util.c
obj/rational.o: src/rational.c
obj/main.o: src/main.c

egc: ${OBJ}

