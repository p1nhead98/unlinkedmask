#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Music.h"
#include "Scroll.h"
#include "Misc.h"
#include "TileAnimation.h"
#include <gb/gb.h>
#include "Keys.h"
#include "BankManager.h"
#include "MapInfo.h"
#include <string.h>
#include "SGB.h"

IMPORT_MAP(titleScreen);
IMPORT_MAP(lvl_1gp);
IMPORT_MAP(lvl_2);
IMPORT_MAP(lvl_3);
IMPORT_MAP(lvl_4);
IMPORT_MAP(lvl_5);
IMPORT_MAP(lvl_6);
IMPORT_MAP(lvl_7);
IMPORT_MAP(lvl_8);
IMPORT_MAP(lvl_9);
IMPORT_MAP(lvl_10);
IMPORT_MAP(lvl_11);
IMPORT_MAP(lvl_12);
IMPORT_MAP(lvl_13);
IMPORT_MAP(lvl_14);
IMPORT_MAP(lvl_15);
IMPORT_MAP(lvl_16);
IMPORT_MAP(boss2Electric);
IMPORT_MAP(boss3ground);
IMPORT_MAP(window);
IMPORT_MAP(window2);
IMPORT_MAP(windTowerDemo);

IMPORT_MAP(linkedborder);


DECLARE_MUSIC(song1);
DECLARE_MUSIC(unlinkedchainedsoul);
DECLARE_MUSIC(unlinkedrooftop);
DECLARE_MUSIC(unlinkedinside1);
DECLARE_MUSIC(unlinkedtitlescreen);

UINT8 collision_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 33, 34, 35, 36, 37, 38, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 0};
UINT8 collision_tiles2[] = {4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 56, 57, 58, 59, 60, 61, 62, 63, 77, 78, 79, 80, 81, 82, 83, 84, 0};

UINT8 bossfight_col[] = {4, 5, 8, 10, 12, 14, 16, 17, 0};

UINT8 windtower_tiles[] = {10,7,8,9,15,16,17,4,5,6,82,83,84,85,86,87,88,89,18,12, 0};

UINT8 door_time = 0;
UINT8 door_time_btwn = 0;
UINT8 door_time_btwn_start = 0;
UINT8 door_open = 0;
BOOLEAN door_button = 0;
UINT8 current_level = 14;

UINT8 doAnimCount = 0;
UINT8 AnimCounter = 0;

UINT8 IsFirstLvl = 0;

UINT8 start_screen = 0;


struct TilesInfo* original_tiles = 0;
UINT8 original_lvl_bank = 0;

extern UINT8 state_interrupts;


extern UINT8 max_life;
extern UINT8 current_life;
extern UINT8 stop_music_on_new_state;
extern UINT8 on_off;

extern UINT8 can_scroll_x;
extern UINT8 can_scroll_y;

UINT8 event = 0;


IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim2);
IMPORT_TILES(spikesAnim3);
IMPORT_TILES(spikesAnim4);

IMPORT_TILES(waterAnim);
IMPORT_TILES(waterfallAnim);
IMPORT_TILES(waterfallAnim2);


Sprite* player_sprite = 0;



struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels[] = {
	BANKED_MAP(titleScreen),
	BANKED_MAP(lvl_1gp),
	BANKED_MAP(lvl_2),
	BANKED_MAP(lvl_3),
	BANKED_MAP(lvl_4),
	BANKED_MAP(lvl_5),
	BANKED_MAP(lvl_6),
	BANKED_MAP(lvl_7),
	BANKED_MAP(lvl_8),
	BANKED_MAP(lvl_9),
	BANKED_MAP(lvl_10),
	BANKED_MAP(lvl_11),
	BANKED_MAP(lvl_12),
	BANKED_MAP(lvl_13),
	BANKED_MAP(lvl_14),
	BANKED_MAP(lvl_15),
	BANKED_MAP(lvl_16),
	BANKED_MAP(boss2Electric),
	BANKED_MAP(boss3ground),
	BANKED_MAP(windTowerDemo),
};



typedef struct {
    UINT16 start_x;
    UINT16 start_y;
} START_POS;

const START_POS start_positions[] = {
	{8, 0}, //TitleScreen
	{8, 144}, //Level 1 Player Start Position
	{8, 128}, //Level 2 Player Start Position
	{8, 112}, //Level 3 Player Start Position
	{8, 128}, //Level 4 Player Start Position
	{8, 96},  //Level 5 Player Start Position
	{8, 144},  //Level 6 Player Start Position
	{8, 112},  //Level 7 Player Start Position
	{8, 96},  //Level 8 Player Start Position
	{8, 128},  //Level 9 Player Start Position
	{8, 128},  //Level 10 Player Start Position
	{8, 144},  //Level 11 Player Start Position
	{8, 96},  //Level 12 Player Start Position
	{8, 96},  //Level 13 Player Start Position
	{8, 96},  //Level 14 Player Start Position
	{8, 96},  //Level 15 Player Start Position
	{8, 144},  //Level 16 Player Start Position
	{100, 130},  //Level 17 Player Start Position
	{22, 130},  //Level 18 Player Start Position
	{22, 126},  //Level 19 Player Start Position
};








void START()
{

	// LY_REG  = 0;
	// disable_interrupts();
	// add_LCD(LCD_Interrupt);
	// add_VBL(VBL_Interrupt);
	// enable_interrupts();
	
	if(current_level == 0){
		DISPLAY_OFF;
		LOAD_SGB_BORDER(linkedborder);
		DISPLAY_ON;
	}
	can_scroll_x = 1;
	stop_music_on_new_state = 0;
	event = 0;
	// current_level = 9;
	const struct MapInfoBanked* level = &levels[current_level];
	
	
	door_open = 0;
	door_button = 1;
	door_time = 6;

	doAnimCount = 3;
	AnimCounter = 0;
	
	on_off = 0;

	current_life = max_life;

	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);

	start_screen = 0;

	
	if(current_level != 0){
		if(current_level != 17 && current_level != 18){
			INIT_HUD(window);
		}else{
			INIT_HUD(window2);
		}
	}else{
		HIDE_WIN;
	}


	

	if( current_level < 11){
		InitScroll(level->bank, level->map, collision_tiles, 0);
	}else if( current_level > 10){
		InitScroll(level->bank, level->map, collision_tiles2, 0);
	}
	
	//InitScroll(level->bank, level->map, windtower_tiles, 0);

	if(current_level == 1){
		IsFirstLvl = 1;
	}else{
		IsFirstLvl = 0;
	}

	if(current_level != 0){
		if(current_level != 17 && current_level != 18){
			if( current_level < 6){
				player_sprite = scroll_target = SpriteManagerAdd(SpritePlayerNoCape, start_positions[current_level].start_x, start_positions[current_level].start_y);
			}else if( current_level > 5){
				player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, start_positions[current_level].start_x, start_positions[current_level].start_y);
			}
			
		}else{
			
			if(current_level == 17){
				SpriteManagerAdd(SpriteBossElec, 8, 121);
				player_sprite = SpriteManagerAdd(SpritePlayer, start_positions[current_level].start_x, start_positions[current_level].start_y);
			}
			if(current_level == 18){
				player_sprite = SpriteManagerAdd(SpritePlayer, start_positions[current_level].start_x, start_positions[current_level].start_y);
				SpriteManagerAdd(SpriteCrystalBoss, 123, 128);
			}
			
		}

	}

	
	switch (current_level)
	{
	case 0:
		PlayMusic(unlinkedtitlescreen, 1);
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
		PlayMusic(unlinkedchainedsoul, 1);
		ScrollRelocateMapTo(0,48);
		break;
	case 7:
		ScrollRelocateMapTo(0,48);
		break;
	case 8:
		ScrollRelocateMapTo(0,48);
		break;
	case 9:
		ScrollRelocateMapTo(0,48);
		break;
	case 10:
		ScrollRelocateMapTo(0,48);
		break;
	case 11:
		PlayMusic(unlinkedinside1, 1);
		
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 35;
		SetOnOffCols(collision_tiles2, on_off);
		break;
	case 12:
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 120;
		SetOnOffCols(collision_tiles2, on_off);
		break;
	case 13:
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 120;
		SetOnOffCols(collision_tiles2, on_off);
		break;
	case 14:
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 200;
		SetOnOffCols(collision_tiles2, on_off);
		SetOnOffColsEvent(collision_tiles2, 0);
		break;
	case 15:
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 220;
		SetOnOffCols(collision_tiles2, on_off);
		break;
	case 16:
		ScrollRelocateMapTo(0,48);
		door_time_btwn_start = door_time_btwn = 220;
		SetOnOffCols(collision_tiles2, on_off);
		break;
	case 17:
		ScrollRelocateMapTo(0,48);
		state_interrupts = 1;
		// door_time_btwn_start = door_time_btwn = 220;
		// SetOnOffCols(collision_tiles2, on_off);
		break;
	case 18:
		ScrollRelocateMapTo(0,40);
		state_interrupts = 2;
		// door_time_btwn_start = door_time_btwn = 220;
		// SetOnOffCols(collision_tiles2, on_off);
		break;
	case 19:
		ScrollRelocateMapTo(0,48);

		// door_time_btwn_start = door_time_btwn = 220;
		// SetOnOffCols(collision_tiles2, on_off);
		break;
	}

	
	

	//set_interrupts(LCD_IFLAG | VBL_IFLAG );
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
		#ifdef CGB
		TMA_REG = _cpu == CGB_TYPE ? 120U : 0xBCU;
#else
		if(current_level > 10){
			TMA_REG = 175u;
		}else if(current_level == 0){
			TMA_REG = 154u;
		}else{
		
			TMA_REG = 180u;
		}
		
#endif

	if(current_level != 0){
		RefreshLife();
	}else{
		HIDE_WIN;
	}
	
	
}

void UPDATE()
{
	// vsync();
	// scanline_offsets = scanline_offsets_tbl + ((sys_time >> 2) & 0x07u)

	if(KEY_TICKED(J_START) ){
		if(current_level == 0){
		
			current_level++;
			SetState(current_state);		
		
		}else{
		start_screen = start_screen == 0 ? 1 : 0;		
		if( start_screen == 1 ){
			DISPLAY_OFF;
			SetWindowY(0);
			SetPauseMenu();
		}else{
			SetWindowY(128);
			SetPauseMenu();
			RefreshLife();
			RefreshTimer(0);
			if(player_sprite->y != 0){
				pDelay(40);
			}
			
		}
		}
	}

	if(current_level != 17 && current_level != 18 && start_screen == 0 ){


		if(--doAnimCount == 0 && current_level > 0){
			
			
			AnimCounter++;
			Tile_Anim(AnimCounter , 2, &spikesAnim, 112, BANK(spikesAnim));
			Tile_Anim(AnimCounter , 2, &spikesAnim2, 114, BANK(spikesAnim2));
			Tile_Anim(AnimCounter , 2, &spikesAnim3, 113, BANK(spikesAnim3));
			Tile_Anim(AnimCounter , 2, &spikesAnim4, 115, BANK(spikesAnim4));
		
			doAnimCount = 5;
		}
		
		if(door_open == 1 && --door_time_btwn == 0){
			
			door_time--; 
			RefreshTimer(door_time);
			door_time_btwn = door_time_btwn_start;
			
		}
		if(door_time == 0){
			door_open = 0;
			door_time = 6;
			door_button = 1;
			SetDoorCols( 0 );
			
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

		} else if(current_level == 18){
			if(--doAnimCount == 0 && current_level > 0){
				
				
				
				AnimCounter++;
				Tile_Anim(AnimCounter , 2, &waterAnim, 47, BANK(waterAnim));
				Tile_Anim(AnimCounter , 8, &waterfallAnim2, 72, BANK(waterfallAnim2));
		
			
				doAnimCount = 5;
			}
	}
	if(current_level == 14 && player_sprite->x > 1142 && can_scroll_x == 1 && event == 0){
		can_scroll_x = 0;
		SetOnOffColsEvent(collision_tiles2, 1);
	}
	if(event == 1){
		can_scroll_x = 1;
		SetOnOffColsEvent(collision_tiles2, 2);
	}
	
}
