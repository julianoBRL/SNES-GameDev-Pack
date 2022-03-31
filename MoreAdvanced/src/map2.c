#include <snes.h>
#include "utils/mapRender.h"

//---------------------------------------------------------------------------------
extern char mapgfx2, mapgfx2_end;
extern char mappal2;
extern char map2;
extern char mapcol2;

//---------------------------------------------------------------------------------

static void renderMap2(void){
	u16 i;
	for(i=0;i<32;i++){
		dmaCopyVram(&map2+64*i, 0x1000+32*i, 64);
	}
}

/*u16 getCollisionTile(u16 x, u16 y) {
	u16 *ptrMap = (u16 *) &mapcol2 + (y>>3)*300 + (x>>3);
	return (*ptrMap);
}*/


//---------------------------------------------------------------------------------
void loadMap2(void) {

	unsigned short pad0;

	bgInitTileSet(1, &mapgfx2, &mappal2, 0, (&mapgfx2_end - &mapgfx2), 32*2, BG_256COLORS, 0x6000);
	
	// Init Map to address 0x1000 and Copy Map to VRAM
	bgSetMapPtr(1, 0x1000, SC_32x32);

	//dmaCopyVram(&map + 300, (Screen start addr)+(eixo Y)*(eixo X), (tamanho));
	//Eixo X tem cascade(se o sprite sair da tela ele cai para a linha de baixo)
	//dmaCopyVram(&map + 300*2, 0x1000+(3-1)*32, 32*2); 26*32 = 832 (emcaixe perfeito) 768

	renderMap2();
    
    setBrightness(0xF);
	WaitForVBlank();
	while(1) {
		pad0 = padsCurrent(0);


		switch (pad0){
			case KEY_RIGHT: moveLevelY(W_RIGHT,1,32); 	break;
			case KEY_LEFT: 	moveLevelY(W_LEFT,1,32); 	break;
			case KEY_UP: 	moveLevelY(W_DOWN,1,32); 	break;
			case KEY_DOWN: 	moveLevelY(W_UP,1,32); 		break;
		}
		WaitForVBlank();
	}
	return 0;
}