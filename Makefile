NUM_CORES := $(shell grep -c ^processor /proc/cpuinfo)
MAKEFLAGS += --jobs=$(NUM_CORES) --max-load=$(NUM_CORES)

PROG := sstl

SRC_DIR := test
BIN_DIR := bin
INT_DIR := $(BIN_DIR)/intermediates

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.o))
DEPS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.d))

INCLUDE_PATH := -I inc
INCLUDE_PATH += -I vendor

CXX      := g++
CPPFLAGS := --std=c++98 -Wall -Wextra -Werror -O0 $(INCLUDE_PATH)
LDFLAGS  :=

QUIET := @

.PHONY: all test
all: test

test: $(PROG)
	$(QUIET)$(BIN_DIR)/$(PROG) --use-colour yes --order rand --rng-seed time

$(PROG): $(OBJS)
	$(QUIET)echo 'Linking ...'
	$(QUIET)$(CXX) $(LDFLAGS) -o $(BIN_DIR)/$@ $^

$(INT_DIR):
	$(QUIET)mkdir -p $(INT_DIR)

$(INT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INT_DIR)
	$(QUIET)echo 'Compiling $< ...'
	$(QUIET)$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	$(QUIET)echo 'Cleaning ...'
	$(QUIET)rm -rf ./$(BIN_DIR)
