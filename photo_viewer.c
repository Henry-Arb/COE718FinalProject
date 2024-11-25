#include "GLCD.h"
#include "KBD.h"
#include "photo_viewer.h"
#include "ferrari.h"
#include "mclaren.h"
#include "utilities.h"
#include "porsche.h"


void display_image(int sel){
	switch(sel){
		
		case 0:
				GLCD_Clear(White);
				GLCD_Bitmap(60, 45, FERRARI_WIDTH, FERRARI_HEIGHT, FERRARI_PIXEL_DATA); 
		break;
		
		case 1:
				GLCD_Clear(White);
				GLCD_Bitmap(60, 45, MCLAREN_WIDTH, MCLAREN_HEIGHT, MCLAREN_PIXEL_DATA);
		break;
	
		case 2:
				GLCD_Clear(White);
				GLCD_Bitmap(60, 45, PORSCHE_WIDTH, PORSCHE_HEIGHT, PORSCHE_PIXEL_DATA); 
		break;
	}
}

int photo_viewer(void){
	int sel = 0;
	display_image(sel);
	while(1){
			switch(get_button()){
			case KBD_DOWN:
				sel += 1;
				sel = sel % 2; // Loop back to first choice.
				display_image(sel);
			break;
			
			case KBD_UP:
				sel -= 1;
				sel = MAX(sel, 0); // Zero as the minimum possible option.
				display_image(sel);
			break;
			
			case KBD_LEFT:
				return 0;
			break;
	}
}
};