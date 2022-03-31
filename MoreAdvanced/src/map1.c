#include <snes.h>
#include "utils/mapRender.h"

//---------------------------------------------------------------------------------
extern char mapgfx, mapgfx_end;
extern char mappal;
extern char map;
extern char mapcol;
extern char playergfx, playergfx_end;
extern char playerpal;

#define GRAVITY 48
#define JUMPVALUE (GRAVITY*20)
#define FRAMES_PER_ANIMATION 7

//---------------------------------------------------------------------------------
// Player sprite
typedef struct
{
	unsigned int x, y;
	int jmpval;
	int anim_frame;
	int flipx;
	int gfx_frame;
    
} Player;

Player player;
u16 pad0, move, i;                  // loop & pad variable
//---------------------------------------------------------------------------------

int idleAnimation[7] = {0,1,2,3,2,1,0};
int fallAnimation[9] = {3,4,5,6,7,6,5,4,3};
int jumpAnimation[7] = {16,17,18,19,18,17,16};
int walkAnimation[9] = {19,20,21,22,23,22,21,20,19};

//---------------------------------------------------------------------------------
static void renderMap(){
	for(i=0;i<32;i++){
		dmaCopyVram(&map+64*i, 0x1000+32*i, 64);
	}
}

static u16 getCollisionTile(u16 x, u16 y) {
	u16 *ptrMap = (u16 *) &mapcol + (y>>3)*32 + (x>>3);
	return (*ptrMap);
}

//---------------------------------------------------------------------------------
static void renderAnimation(int animation[]){
	player.gfx_frame = animation[player.anim_frame];
	if(snes_vblank_count % 10 == 0) player.anim_frame++;
	if(player.anim_frame >= sizeof(animation)) player.anim_frame = 0;
	oamSet(0,  player.x>>8, player.y>>8, 3, player.flipx, 0, player.gfx_frame*2, 0);
}
//---------------------------------------------------------------------------------
void moveplayer() {

	if (pad0 & (KEY_RIGHT | KEY_LEFT | KEY_A) ) {

		if (pad0 & KEY_RIGHT) { 

			if (getCollisionTile((player.x>>8)+16, (player.y>>8)) == 0) {
				player.x+=256;
				player.flipx=0;
				renderAnimation(walkAnimation);
			}

		}else if (pad0 & KEY_LEFT)  {

			if (getCollisionTile((player.x>>8)-1, (player.y>>8)) == 0) { 
				player.x-=256;
				player.flipx=1;
				renderAnimation(walkAnimation);
			}

		}else{renderAnimation(idleAnimation);}

		if (pad0 & KEY_A) {
			
			if (getCollisionTile((player.x>>8)+15, (player.y>>8)+16) != 0 || getCollisionTile((player.x>>8), (player.y>>8)+16) != 0) {
				player.jmpval = -JUMPVALUE;
				renderAnimation(jumpAnimation);
			}

		}
		
	}else{
		renderAnimation(idleAnimation);
	}

	// if can jump, just do it !
	if (getCollisionTile((player.x>>8)+15, (player.y>>8)+16) == 0 || getCollisionTile((player.x>>8), (player.y>>8)+16) == 0) {
		player.jmpval += GRAVITY;
	}
	
	// Add jumping value if needed
	player.y += player.jmpval;

	if(getCollisionTile((player.x>>8)+16, (player.y>>8)-1) != 0 || getCollisionTile((player.x>>8)+1, (player.y>>8)-1) != 0){
		player.jmpval = 0;
	}

	
	//se for menos de afasta do player se for mais se aproxima do player

	//consoleNocashMessage("cima direita = %s", (getCollisionTile((player.x>>8)+16, (player.y>>8)-1) != 0)?"true\n":"false\n");
	//cima direita
	
	//consoleNocashMessage("cima esquerda = %s", (getCollisionTile((player.x>>8)+1, (player.y>>8)-1) != 0)?"true\n":"false\n");
	//cima esquerda

	//consoleNocashMessage("chão esquerda = %s", (getCollisionTile((player.x>>8), (player.y>>8)+16) == 0)?"true\n":"false\n");
	//chão esquerda

	//consoleNocashMessage("chão direita = %s", (getCollisionTile((player.x>>8)+15, (player.y>>8)+16) == 0)?"true\n":"false\n");
	//chão direita

	//consoleNocashMessage("direita = %s", (getCollisionTile((player.x>>8)+16, (player.y>>8)) != 0)?"true\n":"false\n");
	//direita

	//consoleNocashMessage("esquerda = %s", (getCollisionTile((player.x>>8)-1, (player.y>>8)) != 0)?"true\n":"false\n");
	//esquerda

	//consoleNocashMessage("\n");
	
	// To avoid being in floor
	while (getCollisionTile(((player.x>>8)+8), ((player.y>>8)+15))) {
		player.y -= 128; 
		player.jmpval = 0;
	}
	
}

//---------------------------------------------------------------------------------
void loadMap1(void) {

	bgInitTileSet(1, &mapgfx, &mappal, 0, (&mapgfx_end - &mapgfx), 32*2, BG_256COLORS, 0x6000);
	
	// Init Map to address 0x1000 and Copy Map to VRAM
	bgSetMapPtr(1, 0x1000, SC_32x32);  bgSetEnable(1);

	//dmaCopyVram(&map + 300, (Screen start addr)+(eixo Y)*(eixo X), (tamanho));
	//Eixo X tem cascade(se o sprite sair da tela ele cai para a linha de baixo)
	//dmaCopyVram(&map + 300*2, 0x1000+(3-1)*32, 32*2); 26*32 = 832 (emcaixe perfeito) 768

	// Init Sprites gfx and palette with default size of 16x16
	oamInitGfxSet(&playergfx, (&playergfx_end-&playergfx), &playerpal, 16*2, 0, 0x4000, OBJ_SIZE16_L32);

	renderMap(map);

	// Show Player
	//player.x = (pixels)*(quantidade de pixels a mover o sprite)<<8;
	//cada quadrado no grid tem 8 pixels, o sprite de move de 8 em 8 pixels
	//eixo de ancora no 1° sprite
	player.x = ((8*(3*2))+1)<<8; 
	player.y = ((8*(5*2))-1)<<8;
	player.anim_frame = 1; player.flipx = 0; player.jmpval = 0;
	oamSet(0,  (player.x>>8), (player.y>>8), 3, player.flipx, 0, player.anim_frame*2, 0);  // flip x and take 5th sprite
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
    
    setBrightness(0xF);
	WaitForVBlank();

	while(1) {
		pad0 = padsCurrent(0);

		/*switch (pad0){
			case KEY_RIGHT: moveLevelY(W_RIGHT,1,32); 	break;
			case KEY_LEFT: 	moveLevelY(W_LEFT,1,32); 	break;
			case KEY_UP: 	moveLevelY(W_DOWN,1,32); 	break;
			case KEY_DOWN: 	moveLevelY(W_UP,1,32); 		break;*/

		/*switch (pad0){
			case KEY_RIGHT: renderAnimation(walkAnimation); player.flipx = 0; 	break;
			case KEY_LEFT:  renderAnimation(walkAnimation); player.flipx = 1; 	break;
			case KEY_A:  renderAnimation(jumpAnimation);	break;
			default: renderAnimation(idleAnimation); break;
		}*/
		moveplayer();
		WaitForVBlank();
	}
	return 0;
}