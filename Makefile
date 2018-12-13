CC := gcc
CFLAGS := -Wall -pedantic
INC := -Iinclude
#LIB :=

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/Clinic

SRCEXT := c
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(SOURCES: .$(SRCEXT)=.o)

$(TARGET): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

.PHONY: clean
clean:
	rm -f -r $(BUILDDIR) $(TARGETDIR)

tests:
	$(CC) test/test.c -o $(TARGETDIR)/test $(CFLAGS) $(INC)
