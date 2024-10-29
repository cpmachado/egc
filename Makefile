# See LICENSE for details
# makefile for egc

.PHONY: all clean dist install uninstall
.DEFAULT: all

include config.mk

PKGFILES = \
	CPPLINT.cfg\
	LICENSE\
	Makefile\
	README.md\
	config.mk\
	doc\
	man\
	src

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DIST_DIR = $(BUILD_DIR)/dist
DIST_BASE_DIR = egc-$(VERSION)

LIBEGC_SRC_DIR = src/egc
LIBEGC_OBJ_DIR = $(BUILD_DIR)/obj/egc
LIBEGC_SRC = $(wildcard $(LIBEGC_SRC_DIR)/*.c)
LIBEGC_OBJ = $(patsubst $(LIBEGC_SRC_DIR)/%.c,$(LIBEGC_OBJ_DIR)/%.o, $(LIBEGC_SRC))
LIBEGC_BIN = $(BUILD_DIR)/libegc.a

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))
BIN = $(BIN_DIR)/egc


all: $(BIN)
	@echo "egc built"

clean:
	@echo cleaning
	@rm -rf $(BUILD_DIR)

lint:
	@cppcheck --check-level=exhaustive $(SRC_DIR) include
	@cpplint --recursive $(SRC_DIR) include

options:
	@echo "egc compilation flags"
	@echo "VERSION    = $(VERSION)"
	@echo "CC         = $(CC)"
	@echo "CFLAGS     = $(CFLAGS)"
	@echo "CPPFLAGS   = $(CPPFLAGS)"
	@echo "LDFLAGS    = $(LDFLAGS)"
	@echo "LIBEGC_SRC = $(LIBEGC_SRC)"
	@echo "LIBEGC_OBJ = $(LIBEGC_OBJ)"
	@echo "LIBEGC_BIN = $(LIBEGC_BIN)"
	@echo "SRC        = $(SRC)"
	@echo "OBJ        = $(OBJ)"
	@echo "BIN        = $(BIN)"


dist:
	mkdir -p $(DIST_DIR)/$(DIST_BASE_DIR)
	cp -r $(PKGFILES) $(DIST_DIR)/$(DIST_BASE_DIR)
	cd $(DIST_DIR); \
	tar -cz  -f $(DIST_BASE_DIR).tar.gz $(DIST_BASE_DIR); \
	zip -r $(DIST_BASE_DIR).zip $(DIST_BASE_DIR)

install: egc
	@echo installing executable file to $(PREFIX)/bin
	@mkdir -p $(PREFIX)/bin
	@cp -f $(BIN) $(PREFIX)/bin
	@chmod 755 $(PREFIX)/bin/egc

uninstall:
	@echo removing executable file from $(PREFIX)/bin
	@rm -f $(PREFIX)/bin/egc

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBEGC_OBJ_DIR):
	mkdir -p $(LIBEGC_OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIBEGC_BIN): $(LIBEGC_OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(BIN): $(OBJ) $(LIBEGC_BIN) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(LIBEGC_OBJ_DIR)/%.o: $(LIBEGC_SRC_DIR)/%.c | $(LIBEGC_OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
