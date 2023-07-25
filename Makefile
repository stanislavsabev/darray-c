
CC=gcc
CSTANDARD=-std=c17
WFLAGS=-Wall -Wextra
CFLAGS=$(WFLAGS) $(CSTANDARD)

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
OBJ_DEBUG_DIR=$(OBJ_DIR)/debug
BIN_DEBUG_DIR=$(BIN_DIR)/debug
BIN_NAME=main

BUILD_TARGET=Debug

# compile macros
BIN_NAME := main
ifeq ($(OS),Windows_NT)
	BIN_NAME := $(addsuffix .exe,$(BIN_NAME))
endif

BIN_TARGET := $(BIN_DIR)/$(BIN_NAME)
BIN_DEBUG_TARGET := $(BIN_DEBUG_DIR)/$(BIN_NAME)

ifeq ($(BUILD_TARGET), Debug)
	TARGET:=build_debug
else ifeq ($(BUILD_TARGET), Release)
	TARGET:=build_release
else
	TARGET:=all
endif


# src files & obj files
SRCS := $(foreach x, $(SRC_DIR), $(wildcard $(addprefix $(x)/*,.c*)))
OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))
OBJS_DEBUG := $(addprefix $(OBJ_DEBUG_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

# clean files list
CLEAN_LIST := $(BIN_DIR) $(OBJ_DIR)

# default rule
default: build

.PHONY: help
help: ## Show this message
	@awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make \033[36m<BIN_target>\033[0m\n\nTargets:\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-10s\033[0m\t% s\n", $$1, $$2 }' $(MAKEFILE_LIST)

.PHONY: all
all: build_release build_debug

# non-phony targets
$(BIN_TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c*
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DEBUG_DIR)/%.o: $(SRC_DIR)/%.c*
	$(CC) $(CFLAGS) -g -c $^ -o $@

$(BIN_DEBUG_TARGET): $(OBJS_DEBUG)
	$(CC) $(CFLAGS) -g  $^ -o $@
 
# phony rules
.PHONY: build
build: $(TARGET) ## Build current target (Debug/Release)

.PHONY: build_release
build_release: makedir $(BIN_TARGET) ## Build Release
	@printf "build: OK\n"

.PHONY: build_debug
build_debug: makedir $(BIN_DEBUG_TARGET) ## Build Debug
	@printf "build debug: OK\n"

.PHONY: rebuild
rebuild: clean build build_debug

.PHONY: debug
debug: build_debug ## Run Debug
	@printf "debug: "
	./$(BIN_DEBUG_TARGET)

.PHONY: run
run: build ## Run Release
	@printf "run: "
	./$(BIN_TARGET)

.PHONY: makedir
makedir: ## Create buld directories
	@mkdir -p $(BIN_DIR) $(OBJ_DIR) $(OBJ_DEBUG_DIR) $(BIN_DEBUG_DIR)

.PHONY: clean
clean: ## Clean build directories
	@echo Clean $(CLEAN_LIST)
	@rm -rf $(CLEAN_LIST)
