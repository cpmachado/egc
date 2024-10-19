# See LICENSE for details
# makefile for egc

.PHONY: all clean dist install uninstall
.DEFAULT: all

include config.mk

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))
BIN = $(BIN_DIR)/egc


all: ${BIN}
	@echo "egc built"


clean:
	@echo cleaning
	@rm -rf $(BUILD_DIR)

lint:
	@cpplint --recursive $(SRC_DIR)

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

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN): ${OBJ} | $(BIN_DIR)
	${CC} -o $@ $^ ${LDFLAGS}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/egc.o: $(SRC_DIR)/egc.c
