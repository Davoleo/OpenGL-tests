# Compiler settings
CC = g++
WARN_FLAGS = -Wall -Wextra
INCLUDE_FLAG = -Ilib/include
LIB_FLAG = -Llib/impl

# C++ Standard
STDVER_FLAG = -std=c++17

# libraries
GLFW_FLAG = -lglfw3
GLEW_FLAG = -l:glew32.lib
GLEWS_FLAG = -l:glew32s.lib

BUILD = build
BIN = bin

####

main: dircheck $(BIN)/application
	./$(BUILD)/application

$(BIN)/application: $(wildcard build/*.o)
	$(CC) $(LIB_FLAG) $(GLFW_FLAG) $(GLEW_FLAG) $(GLEWS_FLAG) $^ -o $@

$(BUILD)/*.o: $(wildcard src/*.cc)
	$(CC) $(WARN_FLAGS) $(INCLUDE_FLAG) $(STDVER_FLAG) -c $^ -o $@

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