include config.mk

SRC=$(wildcard \
	$(SRCDIR)/main.c \
	$(SRCDIR)/ai/*.c)

OBJ=$(call src2obj,$(SRC))


all: $(OBJ)
	$(LK) $(OBJ) -o $(BINDIR)/$(BINARY)

install:
	cp $(BINDIR)/$(BINARY) $(IPATH)

clean:
	rm `find $(OBJDIR) -name *.o`

doc:
	doxygen doxyfile

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)