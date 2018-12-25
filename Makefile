CC := gcc -std=c99
CFLAGS := -Wall -pedantic #-g
INC := -Iinclude/
#LIB :=

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/Clinic

SRCEXT := c
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(SOURCES: .$(SRCEXT)=.o)

$(TARGET): $(OBJECTS)
#Clinic: $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

.PHONY: clean
clean:
	rm -f -r $(BUILDDIR) $(TARGETDIR) Clinic

tests:
	$(CC) test/test.c -o $(TARGETDIR)/test $(CFLAGS) $(INC)
