#include "KBD.h"
#include "GLCD.h" 
#include "game_menu.h"
#include "utilities.h"

int correct = 0;
int answer;
int total = 5;
int choice = 0;

//Handle User Input 
void handle_userInput(){
	
	while(choice == 0 || choice == KBD_RIGHT){
		choice = get_button();
	}
	answer == choice ? correct++ : NULL;
}

//Display Questions
void displayQuestion(int i){
	GLCD_Clear(White);
	switch(i){
		case 0:
			GLCD_DisplayString(3, 0, 1, "1. Is the Cortex M3 a RISC processor?");
			GLCD_DisplayString(9, 0, 1, "Press up for true, bottom for false, and left to return to the main menu.");
			answer = KBD_UP;
		break;
		case 1:
			GLCD_DisplayString(3, 0, 1, "2. ARM Cortex M3 CPU employs an efficient technique to access bit-wise status/data information from peripheral devices");
			GLCD_DisplayString(9, 0, 1, "Press up for true, bottom for false, and left to return to the main menu.");
			answer = KBD_UP;
		break;
		case 2:
			GLCD_DisplayString(3, 0, 1, "3. Conditional execution is a useless feature of ARM CPUs for compact application code");
			GLCD_DisplayString(9, 0, 1, "Press up for true, bottom for false, and left to return to the main menu.");
			answer = KBD_DOWN;
		break;	
		case 3:
			GLCD_DisplayString(3, 0, 1, "4. ARM Cortex M3 CPU is based on Harvard architecture.");
			GLCD_DisplayString(9, 0, 1, "Press up for true, bottom for false, and left to return to the main menu.");
			answer = KBD_DOWN;
		break;
		case 4:
			GLCD_DisplayString(3, 0, 1, "5. ARM Cortex M3 CPU is a 16-bit processor with 16 registers.");
			GLCD_DisplayString(9, 0, 1, "Press up for true, bottom for false, and left to return to the main menu.");
			answer = KBD_DOWN;
		break;
	};
};

//Return User Score
int quizlet_main(){
	int i;
	char result[30];
	GLCD_Clear(White);

	for(i = 0; i < total; i++){
		displayQuestion(i);
		handle_userInput();
		if(choice == KBD_LEFT) break;
	}
	
	if(choice != KBD_LEFT){
		sprintf(result, "You scored %d / %d! Good Job!", correct, total);
	
		GLCD_Clear(White);
		GLCD_DisplayString(3, 0, 1, result);
	
		delay_time();
	}
	return 0;
}