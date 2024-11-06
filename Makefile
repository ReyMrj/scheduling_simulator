# Compiler
CC = gcc
CFLAGS = -Iinclude -Wall -g

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/scheduling_simulator

# Targets
all: $(EXEC)

# Build executable
$(EXEC): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
