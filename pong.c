#include "game_menu.h"
#include "GLCD.h"
#include "KBD.h"
#include <stdlib.h>

#define SCREEN_WIDTH 19  // Screen width (19 pixels)
#define SCREEN_HEIGHT 20 // Screen height (20 pixels)
#define PADDLE_WIDTH 6   // Paddle width (6 pixels)
#define PADDLE_HEIGHT 1  // Paddle height (1 row)
#define BALL_SIZE 1      // Ball size (1 pixel)
#define BRICK_WIDTH 3    // Brick width (3 pixels)
#define BRICK_HEIGHT 1   // Brick height (1 row)

typedef struct {
    int x, y;  // Position
    int dx, dy;  // Speed (direction)
} Ball;

typedef struct {
    int x, y;  // Position
} Paddle;

typedef struct {
    int x, y;  // Position
    int alive;  // Whether the brick is still intact
} Brick;

// Game objects
Ball ball = {9, 10, 1, -1};  // Starting position and speed for the ball
Paddle paddle = {7, 18};  // Starting position for the paddle
Brick bricks[5][6];  // 5 rows, 6 columns of bricks (adjusted for the screen size)

void initBricks() {
    int i, j;
    // Initialize bricks on the screen
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            bricks[i][j].x = j * BRICK_WIDTH;
            bricks[i][j].y = i * BRICK_HEIGHT;
            bricks[i][j].alive = 1;  // Bricks are initially alive
        }
    }
}

void drawBall() {
    GLCD_SetBackColor(Yellow);  // Ball color (Yellow)
    GLCD_DisplayString(ball.y, ball.x, 1, " ");  // Ball position with yellow background
}

void drawPaddle() {
    int i;
    GLCD_SetBackColor(Black);  // Paddle color (Black)
    // Draw paddle as a series of black squares
    for (i = 0; i < PADDLE_WIDTH; i++) {
        GLCD_DisplayString(paddle.y, paddle.x + i, 1, " ");  // Paddle position with black background
    }
}

void drawBricks() {
    int i, j, k;
    GLCD_SetBackColor(Blue);  // Brick color (Blue)
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (bricks[i][j].alive) {
                // Draw brick as a blue square
                for (k = 0; k < BRICK_WIDTH; k++) {
                    GLCD_DisplayString(bricks[i][j].y, bricks[i][j].x + k, 1, " ");  // Brick position with blue background
                }
            }
        }
    }
}

void moveBall() {
	  int i, j;
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Ball collision with walls
    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_SIZE) {
        ball.dx = -ball.dx;  // Bounce off the sides
    }
    if (ball.y <= 0) {
        ball.dy = -ball.dy;  // Bounce off the top
    }

    // Ball collision with paddle
    if (ball.y + BALL_SIZE >= paddle.y && ball.x >= paddle.x && ball.x <= paddle.x + PADDLE_WIDTH) {
        ball.dy = -ball.dy;  // Bounce off the paddle
    }

    // Ball collision with bricks
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (bricks[i][j].alive && ball.x + BALL_SIZE >= bricks[i][j].x && ball.x <= bricks[i][j].x + BRICK_WIDTH &&
                ball.y + BALL_SIZE >= bricks[i][j].y && ball.y <= bricks[i][j].y + BRICK_HEIGHT) {
                
                // Brick collision
                bricks[i][j].alive = 0;  // Destroy the brick
                ball.dy = -ball.dy;  // Bounce the ball off the brick
            }
        }
    }
}

int checkWin() {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (bricks[i][j].alive) {
                return 0;  // Return 0 if there are still bricks alive
            }
        }
    }
    return 1;  // Return 1 if all bricks are destroyed (win condition)
}


void movePaddle() {
    // Polling for left and right paddle movement
    if (get_button() == KBD_LEFT && paddle.x > 0) {
        paddle.x -= 1;  // Move left
    }
    if (get_button() == KBD_RIGHT && paddle.x < SCREEN_WIDTH - PADDLE_WIDTH) {
        paddle.x += 1;  // Move right
    }
}

void drawGame() {
    GLCD_Clear(White);  // Clear the screen
    drawBricks();  // Draw all the bricks
    drawBall();    // Draw the ball
    drawPaddle();  // Draw the paddle
}

void startPongGame() {
    initBricks();  // Set up the bricks
    
    while (1) {
			  int i;
        moveBall();     // Update ball movement
        movePaddle();   // Handle paddle movement
        drawGame();     // Refresh the screen with updated positions
			
				 // Check for win condition
        if (checkWin()) {
            GLCD_Clear(White);  // Clear the screen with white
            GLCD_DisplayString(0, 0, 1, "You Win!");
            GLCD_DisplayString(1, 0, 1, "Press any key to return to Menu...");
            while (get_button() == 0);  // Wait for user input (exit to menu)
            return;  // Exit the Pong game and return to the game menu
        }

        // Ball falls off the screen (game over condition)
        if (ball.y >= SCREEN_HEIGHT) {
            GLCD_Clear(White);  // Clear the screen with white
            GLCD_DisplayString(0, 0, 1, "Game Over");
            GLCD_DisplayString(1, 0, 1, "Press any key to return to Menu...");
            while (get_button() == 0);  // Wait for user input (exit to menu)
            return;  // Exit the Pong game and return to the game menu
        }

        // Simple delay loop for smooth gameplay (adjustable for frame rate control)
        for (i = 0; i < 10000; i++);  // Delay (can be optimized)
    }
}
