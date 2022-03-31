
#include <snes.h>

int main(void) {

	consoleInit(); 
	setMode(BG_MODE1,0);
	setBrightness(0xF);  

	while(1) {

		WaitForVBlank();

	}
	
	return 0;
}