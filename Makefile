CFLAGS = -g -std=c99 -Wall $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
SRC_DIR = ./src
BUILD_DIR = ./build
SOURCES= $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
OUTPUT = $(BUILD_DIR)/game

all: build

build: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)
