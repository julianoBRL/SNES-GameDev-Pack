#include <snes.h>

extern char gfxpsrite, gfxpsrite_end;
extern char palsprite, palsprite_end;

//---------------------------------------------------------------------------------
int main(void) {

	consoleInit();
	oamInitGfxSet(&gfxpsrite, (&gfxpsrite_end-&gfxpsrite), &palsprite, (&palsprite_end-&palsprite), 0, 0x0000, OBJ_SIZE32_L64);
	oamSet(0,  100, 100, 3, 0, 0, 0, 0);
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
	setMode(BG_MODE1,0); bgSetDisable(0); bgSetDisable(1); bgSetDisable(2);
	setScreenOn();
	
	while(1) {
		WaitForVBlank();
	}
	return 0;
}