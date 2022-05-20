#Warning: Ironically the program cannot yet interpret it's own build Makefile
SHELL = /bin/sh
 CXX = g++ -std=c++17
#CXX = clang++ -std=c++17
CXXFLAGS = -Wall -pedantic -Wextra -Werror -g -Og -I. -I$(HEADDIR)
LDFLAGS = -g -Og

HEADDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

TARGET = $(BINDIR)/makeclone
HEADS = $(wildcard $(HEADDIR)/*.h $(HEADDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: $(BINDIR) $(OBJDIR) clean run echo

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	valgrind $(TARGET)

echo:
	@echo $(foreach var, $(.VARIABLES), $(info $(var) = $($(var)))) # | grep ...

