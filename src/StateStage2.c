#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Keys.h"
#include "Dialogos.h"
#include "Print.h"
#include "Misc2.h"
#include "WinController.h"
#include "TileAnimation.h"

//Mapas con tiles full color
IMPORT_MAP(lvl_6);
IMPORT_MAP(lvl_7);
IMPORT_MAP(lvl_8);
IMPORT_MAP(lvl_9);
IMPORT_MAP(lvl_10);

//Mapas para DMG
IMPORT_MAP(lvl_6Gb);
IMPORT_MAP(lvl_7Gb);
IMPORT_MAP(lvl_8Gb);
IMPORT_MAP(lvl_9Gb);
IMPORT_MAP(lvl_10Gb);

IMPORT_TILES(spikesAnimSt1);
IMPORT_TILES(spikesAnim2St1);
IMPORT_TILES(forestCloudAnim);

UINT8 stage2_col_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 0};


UINT8 current_stage2 = 0;
UINT8 stage2_counter = 0;
UINT8 stage2_counter_2 = 0;
UINT8 stage2_anim = 0;
UINT8 stage2_anim_2 = 0;

Sprite* moon_1_spr = 0;
Sprite* moon_2_spr = 0;

UINT8 map_width = 0;

extern UINT8 current_level;
extern UINT8 can_scroll_x;
extern UINT8 can_scroll_y;
extern UINT8 pdeath_counter;
extern UINT8 pdeath_counter2;
extern UINT8 max_life;
extern UINT8 current_life;
extern UINT8 state_interrupts;

const struct MapInfoBanked stage2_levels[] = {
	BANKED_MAP(lvl_6),
	BANKED_MAP(lvl_7),
	BANKED_MAP(lvl_8),
	BANKED_MAP(lvl_9),
	BANKED_MAP(lvl_10),


};

const struct MapInfoBanked stage2_levels_gb[] = {
	BANKED_MAP(lvl_6),
	BANKED_MAP(lvl_7),
	BANKED_MAP(lvl_8),
	BANKED_MAP(lvl_9Gb),
	BANKED_MAP(lvl_10Gb),

};

const UINT8 stage2_map_width[] = { 10, 11, 12, 12, 12};

const START_POS stage2_start_positions[] = {
	{0, 144}, 
	{0, 112}, 
	{0, 96}, 
	{0, 128}, 
	{0, 128}, 
};


void START() {
	// current_level = 4;
	const struct MapInfoBanked* st_2_level = _cpu == CGB_TYPE ? &stage2_levels[current_level] : &stage2_levels_gb[current_level]; 

	CRITICAL {
#ifdef CGB
	if (_cpu == CGB_TYPE) {

		TMA_REG = 102u;
			
	}else{
	
		TMA_REG = 180u;
		
	}
#else
	TMA_REG = 180u;
		
#endif
	}


	OBP0_REG = _cpu == CGB_TYPE ? PAL_DEF(3, 0, 1, 2) : PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);
	BGP_REG	 = PAL_DEF(2, 0, 1, 3); 


	can_scroll_x = 1;

	current_life = max_life;

	switch(current_level){

		default:
			
			scroll_target = SpriteManagerAdd(SpritePlayer, stage2_start_positions[current_level].start_x, stage2_start_positions[current_level].start_y);
			InitScroll( st_2_level->bank, st_2_level->map, stage2_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			stage2_counter = stage2_counter_2 = 3;
			
			stage2_anim = stage2_anim_2 = 0;
			state_interrupts = 0;
		break;
	}

	// if(current_level == 0){
	if(_cpu == CGB_TYPE){
		SpriteManagerAdd(SpriteMoon, 0, 64);
		moon_1_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
    	CUSTOM_DATA_BTN* data_1 = (CUSTOM_DATA_BTN*)moon_1_spr->custom_data;
    	data_1->state = 1;
		// moon_2_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
    	// CUSTOM_DATA_BTN* data_2 = (CUSTOM_DATA_BTN*)moon_2_spr->custom_data;
    	// data_2->state = 2;
	}
	map_width = stage2_map_width[current_level];
	// }
    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

}

void UPDATE() {

	if(pdeath_counter == 1){
		if(--pdeath_counter2 == 0){
			pdeath_counter2 = 0;
			pdeath_counter = 0;
			SetState(current_state);
		}
	}

	
	if(--stage2_counter == 0){
		stage2_anim = stage2_anim == 1 ? 0 : 1;
		if(stage2_anim == 0){
			Set_Bkg_Data(&spikesAnimSt1, 112, 4, BANK(spikesAnimSt1));
		}else{
			Set_Bkg_Data(&spikesAnim2St1, 112, 4, BANK(spikesAnim2St1));
		}
		stage2_counter = 5;
	}

	if(_cpu == CGB_TYPE){
		if(--stage2_counter_2 == 0){
			stage2_counter_2 = 3;
			stage2_anim_2++;
			Tile_Anim(stage2_anim_2, 8, &forestCloudAnim, 55, BANK(forestCloudAnim));
		}
	}
		
}
