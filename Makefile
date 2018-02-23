NUM_CORES := $(shell grep -c ^processor /proc/cpuinfo)
MAKEFLAGS += --jobs=$(NUM_CORES) --max-load=$(NUM_CORES)

PROG := sstl

SRC_DIR := test
BIN_DIR := bin
INT_DIR := $(BIN_DIR)/intermediates

EXE := $(BIN_DIR)/$(PROG)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.o))
DEPS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.d))

INCLUDE_PATH := -I inc
INCLUDE_PATH += -I vendor

CXX      := g++
CPPFLAGS := --std=c++98 -Wall -Wextra -Werror -g -O0 $(INCLUDE_PATH)
LDFLAGS  :=

QUIET := @

.PHONY: all test clean

all: test

test: $(EXE)
	$(QUIET)$(EXE) --use-colour yes --order rand --rng-seed time

$(EXE): $(OBJS)
	$(QUIET)echo 'Linking ...'
	$(QUIET)$(CXX) $(LDFLAGS) -o $@ $^

$(INT_DIR):
	$(QUIET)mkdir -p $(INT_DIR)

$(INT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INT_DIR)
	$(QUIET)echo 'Compiling $< ...'
	$(QUIET)$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	$(QUIET)echo 'Cleaning ...'
	$(QUIET)rm -rf ./$(BIN_DIR)
