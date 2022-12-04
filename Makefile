NAME = ft_ping
BUILD_DIR = debug
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug

EXECUTABLE = $(BUILD_DIR)/src/$(NAME)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -B $(BUILD_DIR) -S .

run: build
	$(EXECUTABLE)

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: build run clean re
