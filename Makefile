# See LICENSE for details
# makefile for egc

.PHONY: all clean dist install uninstall test lint
.DEFAULT: all

include config.mk

SRC = ${wildcard *.c}
HDR = ${wildcard *.h}
TEST = ${wildcard tests/*.c}
OBJ = ${patsubst %.c,obj/%.o, ${SRC}}
TEST_OBJ = ${patsubst tests/%.c,obj/%.o, ${TEST}}
TEST_BIN = ${patsubst tests/%.c,%, ${TEST}}
BIN = egc

# Files for distribution
PKGFILES = \
	LICENSE\
	Makefile\
	README.md\
	config.mk\
	man\
	tests\
	${SRC}\
	${HDR}



all: ${BIN}
	@echo "egc built"

clean:
	@echo cleaning
	@rm -rf obj ${BIN} ${TEST_BIN} *.tar.gz *.zip

test: ${TEST_BIN}
	$(foreach t,${TEST_BIN}, ./${t})

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
	@echo "TEST       = ${TEST}"
	@echo "TEST_BIN   = ${TEST_BIN}"


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

lint:
	find . -type f -name "*.c" -exec  indent -psl -br -brf -brs -linux {} \;
	find . -type f -name "*.h" -exec  indent -psl -br -brf -brs -linux {} \;
	find . -type f -name "*~" -exec  rm {} \;

obj/%.o: %.c
	@mkdir -p obj
	${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ $<

obj/%.o: tests/%.c
	@mkdir -p obj
	${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ $<

${BIN}:
	${CC} -o $@ $^ ${LDFLAGS}

${TEST_BIN}:
	${CC} -o $@ $^ ${LDFLAGS}

obj/ds.o: ds.c
obj/egc.o: egc.c
obj/main.o: main.c
egc: ${OBJ}

obj/test-ds.o: tests/test-ds.c
test-ds: obj/test-ds.o obj/ds.o

