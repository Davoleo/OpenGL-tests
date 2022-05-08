# Compiler settings
CC = g++
WARN_FLAGS = -Wall -Wextra
INCLUDE_FLAG = -Ilib/include
LIB_FLAG = -Llib/impl

# C++ Standard
STDVER_FLAG = -std=c++17

# libraries
GLFW_FLAG = -lglfw
GLEW_FLAG = -l:glew32.lib
GLEWS_FLAG = -l:glew32s.lib

BUILD = build

output_dir = build

main:
	$(BUILD)/application
	./$(BUILD)/application

$(BUILD)/application: $(wildcard build/obj/*.o)
	$(CC) $(LIB_FLAG) $(GLFW_FLAG) $(GLEW_FLAG) $(GLEWS_FLAG) ^ -o @

$(BUILD)/obj/*.o: $(wildcard src/*.cc)
	$(CC) $(WARN_FLAGS) $(INCLUDE_FLAG) $(STDVER_FLAG) -c ^ -o @

clean:
	$(BUILD)/*