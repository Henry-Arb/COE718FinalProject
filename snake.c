#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_menu.h"

// Macros variable (HEIGHT, WIDTH)
#define HEIGHT 20
#define WIDTH 40

//Fruit Background of BLUE and 1x1 in size.
//Snake Background of Black start at the center. and length of 1.

// Array to store snake tail coordinates
int snakeTailX[100], snakeTailY[100];
// Snake Length
int snakeLength;
// Score and other flags
int score, key, gameover;
// snake and fruit coordinates.
int x, y, fruitx, fruity;

//Setup the game
void setupSnakeGame(){
	// Flag to signal the gameover 
	gameover = 0;
	
	// Initial coordinates of the fruit
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;
    while (fruitx == 0)
        fruitx = rand() % WIDTH;

    while (fruity == 0)
        fruity = rand() % HEIGHT;

    // Score initialzed
    score = 0;
};

// Function to draw the game field, snake
// and fruit
void drawSnakeGame(){

}

// Function for the movement logic that
// checks eat, move, collisions
void logicSnakeGame(){
	int i,j;
	//Updating snake body
	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;
	for(i = 1; i < snakeLength; i++){
		  prev2X = snakeTailX[i];
      prev2Y = snakeTailY[i];
      snakeTailX[i] = prevX;
      snakeTailY[i] = prevY;
      prevX = prev2X;
      prevY = prev2Y;
	}
	   // Changing the direction of movement of snake
    switch (key) {
    case 1:
        x--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y--;
        break;
    case 4:
        y++;
        break;
    default:
        break;
    }
		
 // If the game is over
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;
        
    // Checks for collision with the tail (o)
    for (j = 0; j < snakeLength; j++) {
        if (snakeTailX[j] == x && snakeTailY[j] == y)
            gameover = 1;
    }

    // If snake reaches the fruit
    // then update the score
    if (x == fruitx && y == fruity) {
        fruitx = rand() % WIDTH;
        fruity = rand() % HEIGHT;
        while (fruitx == 0)
            fruitx = rand() % WIDTH;

        // Generation of new fruit
        while (fruity == 0)
            fruity = rand() % HEIGHT;
        score += 10;
         snakeLength++;
    }
}



void startSnakeGame(){
	setupSnakeGame();
	
	while(!gameover){
		drawSnakeGame();
    logicSnakeGame();
	}
}