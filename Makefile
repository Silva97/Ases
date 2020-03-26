include config.mk

SRC=$(wildcard \
	$(SRCDIR)/main.c \
	$(SRCDIR)/ai/*.c)

OBJ=$(call src2obj,$(SRC))


all: mkdir $(OBJ)
	$(LK) $(OBJ) -o $(BINDIR)/$(BINARY)

mkdir:
	mkdir -p $(OBJDIR)/ai

install:
	cp $(BINDIR)/$(BINARY) $(IPATH)

clean:
	rm `find $(OBJDIR) -name *.o`
	rm $(BINDIR)/ases

doc:
	doxygen

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
