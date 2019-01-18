CC     := g++
TARGET := libcream.so

BINDIR := bin
OBJDIR := obj
SRCDIR := src

SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))
CFLAGS  := -std=c++17 -Wall -Wextra -fPIC
LIB     := -lglfw -lGLEW -lGL -shared
INC     := -I include

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $^ -o $(BINDIR)/$(TARGET) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compilation..."
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	$(RM) -r $(OBJDIR) $(BINDIR)/libcream.so

release:
	$(MAKE) CFLAGS="$(CFLAGS) -O2 -DNDEBUG"

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g"

.PHONY: clean
