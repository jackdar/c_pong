build:
	gcc -Wall -I/opt/homebrew/include -std=c99 ./src/*.c -o game -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

run:
	make && ./game

clean:
	rm game
