CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCDIR = src
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
BINS = $(addprefix $(BINDIR)/, $(notdir $(SRCS:.cpp=)))

.PHONY: all clean

all: $(BINS)

LIBS = -pthread # 默认的动态库
$(BINDIR)/all: LIBS += -lpulse -lpulse-simple

$(BINDIR)/%: $(SRCDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BINS)
