#include <snes.h>

//---------------------------------------------------------------------------------
extern char mapgfx, mapgfx_end;
extern char mappal;
extern char map;
extern char mapcol;
extern char snesfont;

u16 i;                  	// loop & pad variable
int a = 0;

enum MapState {W_DOWN = 0, W_UP = 1, W_RIGHT = 2,  W_LEFT = 3};
u16 scrX,scrY;                           // for screen scrolling

//---------------------------------------------------------------------------------

void renderMap(void){
	for(i=0;i<32;i++){
		dmaCopyVram(&map+64*i, 0x1000+32*i, 64);
	}
}

u16 getCollisionTile(u16 x, u16 y) {
	u16 *ptrMap = (u16 *) &mapcol + (y>>3)*300 + (x>>3);
	return (*ptrMap);
}

//---------------------------------------------------------------------------------
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
	
	/*if (direction == W_RIGHT) {
		scrX++; 
		if ( (scrX &3) == 0) { // to avoid to bee too slow
		    //*(unsigned char *) 0x2115 = 0x80;
			sx = (scrX>>3) & 63;
			sx = (sx + 32);
			if (sx>63) 
				sx = sx - 64;
			else
				sx = (sx-32) + 32*32;
			ptrVRAM = 0x1000 + sx; // screen begin to 0x1000
			ptrMap  = (u16 *)  &map + (scrX >> 3) + 32; 
			// Copy the line in the background but need to wait VBL period
			WaitVBLFlag;
			for (i=0;i<16;i++) {
				u16 value = *ptrMap;
				REG_VMADDLH = ptrVRAM;
				REG_VMDATALH = value ;
				ptrVRAM += 32;
				ptrMap += 300;
			}
		}
	}
	// scroll to the left
	else {
		scrX--; 
		if ( (scrX &3) == 0) { // to avoid to bee too slow
			if (scrX) { // to avoid doing some for 1st tile 
				//*(unsigned char *) 0x2115 = 0x80;
				sx = (scrX>>3) & 63;
				sx = (sx - 1);
				if (sx<0) sx = sx + 64;
				if (sx>31) sx = (sx-32) + 32*32;
				ptrVRAM = 0x1000 + sx; // screen begin to 0x1000
				ptrMap  = (u16 *)  &map + (scrX >> 3) - 1; 
				// Copy the line in the background but need to wait VBL period
				WaitVBLFlag;
				for (i=0;i<16;i++) {
					u16 value = *ptrMap;
					REG_VMADDLH = ptrVRAM;
					REG_VMDATALH = value ;
					ptrVRAM += 32;
					ptrMap += 300;
				}
			}
		}
	}*/

	// now scroll with current value
	bgSetScroll(1,scrX,scrY);
}

//---------------------------------------------------------------------------------
int main(void) {
	unsigned short pad0;

	consoleInit();
	bgInitTileSet(1, &mapgfx, &mappal, 0, (&mapgfx_end - &mapgfx), 32*2, BG_256COLORS, 0x6000);
	consoleInitText(0, 1, &snesfont);
	consoleSetTextCol(RGB5(0,0,0), RGB5(31,31,31));
	
	// Init Map to address 0x1000 and Copy Map to VRAM
	bgSetMapPtr(1, 0x1000, SC_32x32);

	//dmaCopyVram(&map + 300, (Screen start addr)+(eixo Y)*(eixo X), (tamanho));
	//Eixo X tem cascade(se o sprite sair da tela ele cai para a linha de baixo)
	//dmaCopyVram(&map + 300*2, 0x1000+(3-1)*32, 32*2); 26*32 = 832 (emcaixe perfeito) 768

	renderMap();
	setMode(BG_MODE1,0);  bgSetDisable(2);
	setBrightness(0xF);
	scrX=0;
	scrY=0;
  
	WaitForVBlank();
	while(1) {
		pad0 = padsCurrent(0);

		if(pad0 == KEY_LEFT){
			moveLevel(W_LEFT);
		}

		if(pad0 == KEY_RIGHT){
			moveLevel(W_RIGHT);
		}

		switch (pad0){
			case KEY_RIGHT: moveLevel(W_RIGHT); break;
			case KEY_LEFT: 	moveLevel(W_LEFT); 	break;
			case KEY_UP: 	moveLevel(W_DOWN); 	break;
			case KEY_DOWN: 	moveLevel(W_UP); 	break;
		}
		WaitForVBlank();
	}
	return 0;
}