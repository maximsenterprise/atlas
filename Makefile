
GXX = clang++
TEST = ./bin/test
LIBATLAS = ./lib/libatlas.dylib

OBJ = ./obj
BIN = ./bin
LIB = ./lib

LIB_FLAGS = -std=c++20 -I ./include -I $(OPENGL_INCLUDE) -I $(GLFW_INCLUDE) -c -L$(GLWF) -L$(OPENGL) -framework Cocoa -framework CoreFoundation -framework IOKit -framework CoreGraphics
LIB_LIBS = -l$(GLFW_LIB) -l$(OPENGL_LIB)
LIB_LINK = -dynamiclib -L$(GLFW) -L$(OPENGL) -framework Cocoa -framework CoreFoundation -framework IOKit -framework CoreGraphics -framework OpenGL

TEST_FLAGS = -std=c++20 -I ./include -L./lib
TEST_LIBS = -latlas
TEST = ./bin/atlas_test

GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
GLFW_LIB = glfw3
GLFW_INCLUDE = /opt/homebrew/Cellar/glfw/3.4/include

OPENGL = /opt/homebrew/Cellar/glew/2.2.0_1/lib
OPENGL_LIB = GLEW
OPENGL_INCLUDE = /opt/homebrew/Cellar/glew/2.2.0_1/include

SRCS = $(shell find atlas -name "*.cpp")
TEST_SRCS = $(shell find test -name "*.cpp")
OBJS = $(patsubst %.cpp, $(OBJ)/%.o, $(SRCS))

.PHONY: all clean test run

all: $(LIBATLAS)

$(LIBATLAS): $(OBJS)
	@mkdir -p $(@D)
	$(GXX) $(LIB_LINK) $(OBJS) $(LIB_LIBS) -o $(LIBATLAS)

$(OBJS): $(OBJ)/%.o: %.cpp
	@mkdir -p $(@D)
	$(GXX) $(LIB_FLAGS) $< $(LIB_LIBS) -o $@ 

clean:
	rm -rf $(OBJ) $(BIN) $(LIB)
	mkdir -p $(OBJ)
	mkdir -p $(LIB)
	mkdir -p $(BIN)

run: $(TEST)
	$(TEST)

test: $(TEST)
	$(TEST)

$(TEST): $(TEST_SRCS) $(LIBATLAS)
	$(GXX) $(TEST_FLAGS) $(TEST_SRCS) $(TEST_LIBS) -o $(TEST)
