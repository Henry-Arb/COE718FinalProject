#include "game_menu.h"
#include "GLCD.h"
#include "KBD.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))


void displayGameMenu(int sel) {
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayString(0,0,1, "COE718 Final Project");

    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Black);
    GLCD_DisplayString(2,0,1, "Main Menu");

    GLCD_SetTextColor(Black);

    sel == 0 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(4,0,1, "1. Snake");

    sel == 1 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(5,0,1, "2. Quizlet");
	
	  sel == 2 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(6,0,1, "3. Back to Main Menu");
}

void handleGameSelection(int sel){
		switch(sel){
			case 0: 
				GLCD_Clear(White);
				snakegame();
				GLCD_Clear(White);
				displayGameMenu(0);
			break;
			case 1:
				GLCD_Clear(White);
				quizlet_main();
			break;
			case 2:
				GLCD_Clear(White);
			break;
		}
}

int game_menu_main (void){
	
	int sel = 0;
	int fsel = 0;
	
	GLCD_Clear(White);
	displayGameMenu(sel);
	
	while(fsel != 2){
		//Take user input
		switch(get_button()){
			case KBD_DOWN:
				sel += 1;
				sel = sel % 3; // Loop back to first choice.
				displayGameMenu(sel);
			break;
			
			case KBD_UP:
				sel -= 1;
				sel = MAX(sel, 0); // Zero as the minimum possible option.
				displayGameMenu(sel);
			break;
			
			case KBD_RIGHT:
				fsel = sel;
				handleGameSelection(sel); // Handle User Selection;
			break;
		}
	}
	
	return 0;
}