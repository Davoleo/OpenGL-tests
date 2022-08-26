# Compiler settings
CC = c++
WARN_FLAGS = -Wall -Wextra

# C++ Standard
STDVER_FLAG = -std=c++17

# libraries
GLFW_FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
GLEW_FLAG = -lGLEW

BUILD = build
BIN = bin

SRC_FILES = $(wildcard src/*.cc)
OBJ_FILES = $(patsubst src/%.cc, build/%.o, $(SRC_FILES))

####

all: dircheck $(BIN)/application
	./$(BIN)/application

$(BIN)/application: $(OBJ_FILES)
	$(CC) $(GLFW_FLAGS) $(GLEW_FLAG) $^ -o $@

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(WARN_FLAGS) $(STDVER_FLAG) -c $< -o $@

dircheck:
ifeq ("$(wildcard $(BIN))", "")
	@echo -n 'Creating bin/ folder -> '
	@ mkdir $(BIN)
	@echo done
endif
ifeq ("$(wildcard $(BUILD))", "")
	@echo -n 'Creating build/ folder -> '
	@ mkdir $(BUILD)
	@echo done
endif

clean:
	rm $(BUILD)/*
	rm $(BIN)/*

cleanall:
	rm -r $(BUILD)
	rm -r $(BIN)