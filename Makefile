CC := clang
#
# [XOPEN:600 POSIX:200112L] SUSv3 / UNIX 03 / POSIX.1-2001 / XPG6
# [XOPEN:700 POSIX:200809L] SUSv4 / UNIX 08 / POSIX.1-2008 / XPG7
#
PORTABILITY := -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L
#
# CONSISTENCY
#
WARNINGS := #-Wno-long-long -Wall -pedantic -Werror
#
# INSPECTION
#
DEBUG := -g -ggdb
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) -Iinc $(WARNINGS) $(DEBUG)

LDFLAGS := 

HEADERS := $(shell ls inc/*.h)

SOURCES := $(shell ls src/*.c)

pvg: main.c $(HEADERS) $(SOURCES)
	$(CC) $(CCFLAGS) -o $@ $< $(SOURCES) $(LDFLAGS)

inc/page.h: etc/page_generate.c etc/page.svg $(HEADERS) $(SOURCES)
	$(CC) $(CCFLAGS) -o $@ $< $(SOURCES) $(LDFLAGS)
	./page_generate

clean:
	$(RM) pvg page_generate

install: pvg
	sudo cp -p pvg /usr/local/bin

uninstall: clean
	sudo rm /usr/local/bin/pvg

