# Pong in C!

This is my implementation of the popular game Pong in C using the SDL2 graphics library.

<img width="912" alt="c_pong" src="https://github.com/user-attachments/assets/17d1e87e-83b4-4218-a128-e103e6f9dac3" />

## Dependencies
To build the game make sure you have the SDL2 graphics library installed. It can be installed by using the following commands:


```

# On macOS using brew:

brew install sdl2


# On linux using a package manager such as apt:

sudo apt-get install libsdl2-dev

```

## Building and Running

```

cd c_pong
make build

# Finally run with:

make run

```

## Controls

The left paddle is controlled using the `W` and `S` keys, the right paddle is controlled using `↑` and `↓`.

The ball will start in the middle and travel outwards towards a player, the player will then have to hit the ball back to the other player.
Each time the ball is hit, it will speed up by a small amount.

If the ball reaches the out of bounds area behind the players paddle the other player will recieve a point and the ball will be reset to the middle.

This currently continues indefintely but the goal is to eventually have the player who reaches an arbitrary number of points to win the game.
