PROG := sstl_test

SRC_DIR := src
BIN_DIR := bin
INT_DIR := $(BIN_DIR)/intermediates

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.o))
DEPS := $(patsubst $(SRC_DIR)%,$(INT_DIR)%,$(SRCS:.cpp=.d))

CXX      := g++
CPPFLAGS := -Wall -Wextra -Werror -O0 -I ../inc
LDFLAGS  :=

SILENCE := @

.PHONY: all test
all: test

test: $(PROG)
	$(SILENCE)$(BIN_DIR)/$(PROG)

$(PROG): $(OBJS)
	$(SILENCE)echo 'Linking ...'
	$(SILENCE)$(CXX) $(LDFLAGS) -o $(BIN_DIR)/$@ $^

$(INT_DIR):
	$(SILENCE)mkdir -p $(INT_DIR)

$(INT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INT_DIR)
	$(SILENCE)echo 'Compiling $< ...'
	$(SILENCE)$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	$(SILENCE)echo 'Cleaning ...'
	$(SILENCE)rm -rf ./$(BIN_DIR)
