#include <snes.h>
#include "utils/mapRender.h"

#include "map1.c"
#include "map2.c"

extern char snesfont;

bool inMenu = true;
int load = 0;

int main(void) {
	unsigned short pad0;

	consoleInit();
	consoleInitText(0, 1, &snesfont);
	setMode(BG_MODE1,0); bgSetDisable(1); bgSetDisable(2);
	setBrightness(0xF);

	// Put some text
	consoleDrawText(6,7,"Jogo SNES Test");
	consoleDrawText(6,13," A - Load Map1");

	// Put screen on
	setScreenOn();
	
	while(inMenu) {
		pad0 = padsCurrent(0);

		if(pad0 == KEY_A){
			load = 1;
			inMenu = false;
			consoleDrawText(6,7,"                    ");
			consoleDrawText(6,13,"                    ");
		}

		if(pad0 == KEY_B){
			load = 2;
			inMenu = false;
			consoleDrawText(6,7,"                    ");
			consoleDrawText(6,13,"                    ");
		}

		WaitForVBlank();
	}

	if(load == 1){
		loadMap1();
	}

	if(load == 2){
		loadMap2();
	}

	return 0;
}