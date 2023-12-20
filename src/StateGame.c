#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Music.h"
#include "Scroll.h"
#include "Misc.h"
#include <gb/gb.h>


IMPORT_MAP(lvl_1);
IMPORT_MAP(lvl_2);
IMPORT_MAP(window);
DECLARE_MUSIC(song1);

UINT8 collision_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 95, 96, 97, 98, 0};


UBYTE counter;
UINT16 p1, p2;

UINT8 door_time;
UINT8 door_open;
BOOLEAN door_button;
UINT8 current_level = 0;

extern UINT8 max_life;
extern UINT8 current_life;



struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels[] = {
	BANKED_MAP(lvl_1),
	BANKED_MAP(lvl_2),
};

typedef struct {
    UINT16 start_x;
    UINT16 start_y;
} START_POS;

const START_POS start_positions[] = {
	{50, 144},
	{50, 128},
};

void START()
{

	// LY_REG  = 0;
	// disable_interrupts();
	// add_LCD(LCD_Interrupt);
	// add_VBL(VBL_Interrupt);
	// enable_interrupts();
	const struct MapInfoBanked* level = &levels[current_level];

	door_open = 0;
	door_button = 1;
	door_time = 100;
	current_life = max_life;

	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 3, 1, 0);	
	scroll_target = SpriteManagerAdd(SpritePlayer, start_positions[current_level].start_x, start_positions[current_level].start_y);
	
	InitScroll(level->bank, level->map, collision_tiles, 0);
	switch (current_level)
	{
	case 0:
		MoveScroll(0,48);
		break;
	
	case 1:
		MoveScroll(0,48);
		break;
	}
	

	//set_interrupts(LCD_IFLAG | VBL_IFLAG );
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	PlayMusic(song1, LOOP);

	INIT_HUD(window);
	RefreshLife();
	
	
}

void UPDATE()
{
	// vsync();
	// scanline_offsets = scanline_offsets_tbl + ((sys_time >> 2) & 0x07u)
	if(door_open == 1 && --door_time == 0){
		door_open = 0;
		door_time = 100; 
		
	}
}
