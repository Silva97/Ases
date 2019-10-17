BINDIR=bin
OBJDIR=bin/obj
SRCDIR=src
BINARY=ases
IPATH=/usr/local/bin/

LK=cc
CC=cc
CFLAGS=-I include \
	-std=gnu11 \
	-Wall \
	-Werror \
	-pedantic-errors

src2obj = $(subst .c,.o,$(subst $(SRCDIR)/,$(OBJDIR)/, $(1)))