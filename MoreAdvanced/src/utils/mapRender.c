#include <snes.h>

static enum MapState {W_DOWN = 0, W_UP = 1, W_RIGHT = 2,  W_LEFT = 3};

static u16 scrX = 1;
static u16 scrY = 1;

void moveLevel(unsigned char direction) {
	u16 *ptrMap;
	u16 ptrVRAM; 
	unsigned short sx;
	
	REG_VMAIN = VRAM_INCHIGH | VRAM_ADRTR_0B | VRAM_ADRSTINC_1; // set address in VRam for read or write ($2116) + block size transfer ($2115)
	REG_VMADDLH = 0x1000;

	switch (direction){
		case W_RIGHT: scrX++; break;
		case W_LEFT: scrX--; break;
		case W_UP: scrY++; break;
		case W_DOWN: scrY--; break;
	}
	
	bgSetScroll(1,scrX,scrY);
}

void moveLevelX(unsigned char direction, int minX, int maxX) {
	u16 *ptrMap;
	u16 ptrVRAM; 
	unsigned short sx;
	
	REG_VMAIN = VRAM_INCHIGH | VRAM_ADRTR_0B | VRAM_ADRSTINC_1; // set address in VRam for read or write ($2116) + block size transfer ($2115)
	REG_VMADDLH = 0x1000;

	switch (direction){
		case W_RIGHT: scrX++; break;
		case W_LEFT: scrX--; break;
	}

    if(scrX < minX) scrX = minX;
    if(scrX > maxX) scrX = maxX;
	
	bgSetScroll(1,scrX,0);
}

void moveLevelY(unsigned char direction, int minY, int maxY) {
	u16 *ptrMap;
	u16 ptrVRAM; 
	unsigned short sx;
	
	REG_VMAIN = VRAM_INCHIGH | VRAM_ADRTR_0B | VRAM_ADRSTINC_1; // set address in VRam for read or write ($2116) + block size transfer ($2115)
	REG_VMADDLH = 0x1000;

	switch (direction){
		case W_UP: scrY++; break;
		case W_DOWN: scrY--; break;
	}

    if(scrY < minY) scrY = minY;
    if(scrY > maxY) scrY = maxY;
	
	bgSetScroll(1,0,scrY);
}