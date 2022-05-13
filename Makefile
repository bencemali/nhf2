SHELL = /bin/sh
 CXX = g++ -std=c++11
#CXX = clang++ -std=c++11
CXXFLAGS = -Wall -pedantic -Wextra -Werror -g -Og -I. -I./include/
LDFLAGS = -g -Og

BINDIR = ./bin
OBJDIR = ./obj
HEADDIR = .
SRCDIR = .

TARGET = $(BINDIR)/makeclone
HEADS = $(wildcard $(HEADDIR)/*.h $(HEADDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: $(BINDIR) $(OBJDIR) clean run

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	$(TARGET)
