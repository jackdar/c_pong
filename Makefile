CFLAGS = -g -std=c99 -Wall $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
SRC_DIR = ./src
BUILD_DIR = ./build
SOURCES= $(wildcard $(SRC_DIR)/*.c)
OUTPUT = $(BUILD_DIR)/game

build:
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LDFLAGS)

run:
	make build
	$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)
