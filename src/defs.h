#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define ACTOR_WIDTH 15
#define ACTOR_HEIGHT 50
#define ACTOR_START_X 50
#define ACTOR_START_Y (float)WINDOW_HEIGHT / 2 - (float)ACTOR_HEIGHT / 2
#define ACTOR_MOVE_SPEED 5

#define BALL_WIDTH 15
#define BALL_HEIGHT 15
#define BALL_START_X (float)WINDOW_WIDTH / 2 - (float)BALL_WIDTH / 2
#define BALL_START_Y (float)WINDOW_HEIGHT / 2 - (float)BALL_HEIGHT / 2
#define BALL_START_SPEED 2
#define BALL_SPEED_INCREASE 0.25
#define MAX_BALL_SPEED 10

#define PADDLE_EFFECT_MULTIPLIER 0.5

#define FONT_FILE "assets/fonts/OpenSans-Regular.ttf"
#define FONT_SIZE 24
