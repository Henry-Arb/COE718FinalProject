#include <stdio.h>
#include <stdlib.h>
#include "game_menu.h"
#include "GLCD.h"
#include "KBD.h"
#include "usb_audio.h"
#include "photo_viewer.h"
#include "music_icon.h"
#include "utilities.h"

void displayMainMenu(int sel) {
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayString(0,0,1, "COE718 Final Project");

    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Black);
    GLCD_DisplayString(2,0,1, "Main Menu");

    GLCD_SetTextColor(Black);

    sel == 0 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(4,0,1, "1. Games");

    sel == 1 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(5,0,1, "2. Audio Player");

    sel == 2 ? GLCD_SetBackColor(Green) : GLCD_SetBackColor(White);
    GLCD_DisplayString(6,0,1, "3. Image Viewer");
}

void handleSelection(int i){
	switch(i){
		case 0:
			//Game Menu
		break;
			
		case 1:
			//Audio Player
			GLCD_Clear(White);
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString(0,0,1, "MP3 Player");
			GLCD_Bitmap(60, 45, MUSIC_ICON_WIDTH, MUSIC_ICON_HEIGHT, MUSIC_ICON_PIXEL_DATA);
			usb_main();
			delay_time();
		  GLCD_Clear(White);
			displayMainMenu(1);
		break;
		
		case 2:
			//Image Viewer
			GLCD_Clear(White);
			photo_viewer();
			GLCD_Clear(White);
			displayMainMenu(2);
		break;
	}
}


//Main menu of the Program;
int main () {
	int sel = 0;
	//Initialize I/O;
	GLCD_Init();
	KBD_Init();
	
	GLCD_Clear(White);
	displayMainMenu(sel);
	
	while(1){
		//Take user input
		switch(get_button()){
			case KBD_DOWN:
				sel += 1;
				sel = sel % 3; // Loop back to first choice.
				displayMainMenu(sel);
			break;
			
			case KBD_UP:
				sel -= 1;
				sel = MAX(sel, 0); // Zero as the minimum possible option.
				displayMainMenu(sel);
			break;
			
			case KBD_RIGHT:
				handleSelection(sel); // Handle User Selection;
			break;
		}
	}
}