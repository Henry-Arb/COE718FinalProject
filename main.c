#include <stdio.h>
#include <stdlib.h>
#include "game_menu.h"
#include "GLCD.h"
#include "KBD.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))


void handleSelection(int i){
	switch(i){
		case 0:
			//Game Menu
		
		case 1:
			//Audio Player
			GLCD_Clear(White);
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString(0,0,1, "MP3 Player");
			
			
		break;
		
		case 2:
			//Image Viewer
		break;
	}
}

//Main menu of the Program;
int main () {
	int sel = 0;
	//Initialize I/O;
	GLCD_Init();
	KBD_Init();
	
	//Main Menu Text
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0, 1, "COE718 Final Project");
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(2,0,1, "Main Menu");
	
	while(1){
		//Take user input
		switch(get_button()){
			case KBD_DOWN:
				sel += 1;
				sel = sel % 3; // Loop back to first choice.
			break;
			
			case KBD_UP:
				sel -= 1;
				sel = MAX(sel, 0); // Zero as the minimum possible option.
			break;
			
			case KBD_RIGHT:
				handleSelection(sel); // Handle User Selection;
			break;
		}
	}
}