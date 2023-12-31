#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Music.h"
#include "Scroll.h"
#include "Misc.h"
#include <gb/gb.h>
#include "Keys.h"


IMPORT_MAP(lvl_1);
IMPORT_MAP(lvl_2);
IMPORT_MAP(lvl_3);
IMPORT_MAP(lvl_4);
IMPORT_MAP(lvl_5);
IMPORT_MAP(lvl_6);
IMPORT_MAP(lvl_7);
IMPORT_MAP(lvl_8);
IMPORT_MAP(window);
DECLARE_MUSIC(song1);

UINT8 collision_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 33, 34, 35, 36, 37, 38, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 0};


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
	BANKED_MAP(lvl_3),
	BANKED_MAP(lvl_4),
	BANKED_MAP(lvl_5),
	BANKED_MAP(lvl_6),
	BANKED_MAP(lvl_7),
	BANKED_MAP(lvl_8),
};

typedef struct {
    UINT16 start_x;
    UINT16 start_y;
} START_POS;

const START_POS start_positions[] = {
	{50, 144}, //Level 1 Player Start Position
	{50, 128}, //Level 2 Player Start Position
	{50, 112}, //Level 3 Player Start Position
	{50, 128}, //Level 4 Player Start Position
	{50, 96},  //Level 5 Player Start Position
	{50, 144},  //Level 6 Player Start Position
	{50, 112},  //Level 7 Player Start Position
	{50, 96},  //Level 8 Player Start Position
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
		ScrollRelocateMapTo(0,48);
		break;
	case 1:
		ScrollRelocateMapTo(0,48);
		break;
	case 2:
		ScrollRelocateMapTo(0,48);
		break;
	case 3:
		ScrollRelocateMapTo(0,48);
		break;
	case 4:
		ScrollRelocateMapTo(0,48);
		break;
	case 5:
		ScrollRelocateMapTo(0,48);
		break;
	case 6:
		ScrollRelocateMapTo(0,48);
		break;
	case 7:
		ScrollRelocateMapTo(0,48);
		break;
	case 8:
		ScrollRelocateMapTo(0,48);
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
	if (KEY_TICKED(J_SELECT) && !KEY_PRESSED(J_LEFT))
	{
		current_level++;
		SetState(current_state);
	} else if (KEY_TICKED(J_SELECT) && KEY_PRESSED(J_LEFT))
	{
		current_level--;
		SetState(current_state);
	}
}
