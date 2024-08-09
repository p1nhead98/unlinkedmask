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

IMPORT_MAP(lvl_1);
IMPORT_MAP(lvl_2);
IMPORT_MAP(lvl_3);
IMPORT_MAP(lvl_4);
IMPORT_MAP(lvl_5);

IMPORT_TILES(spikesAnimSt1);
IMPORT_TILES(spikesAnim2St1);

UINT8 stage1_col_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 33, 34, 35, 36, 37, 38, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 0};


UINT8 current_stage1 = 0;
UINT8 stage1_counter = 0;
UINT8 stage1_anim = 0;

extern UINT8 current_level;
extern UINT8 can_scroll_x;
extern UINT8 can_scroll_y;
extern UINT8 pdeath_counter;
extern UINT8 pdeath_counter2;
extern UINT8 max_life;
extern UINT8 current_life;
extern UINT8 state_interrupts;

const struct MapInfoBanked stage1_levels[] = {
	BANKED_MAP(lvl_1),
	BANKED_MAP(lvl_2),
	BANKED_MAP(lvl_3),
	BANKED_MAP(lvl_4),
	BANKED_MAP(lvl_5),

};

const START_POS stage1_start_positions[] = {
	{0, 160}, 
	{0, 128}, 
	{0, 112}, 
	{0, 128}, 
	{0, 96}, 
};


void START() {
	const struct MapInfoBanked* st_1_level = &stage1_levels[current_level]; 

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


	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);
	BGP_REG	 = PAL_DEF(2, 0, 1, 3); 

	can_scroll_x = 1;

	current_life = max_life;

	switch(current_level){

		default:
			
			scroll_target = SpriteManagerAdd(SpritePlayerNoCape, stage1_start_positions[current_level].start_x, stage1_start_positions[current_level].start_y);
			InitScroll(st_1_level->bank, st_1_level->map, stage1_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			stage1_counter = 3;
			stage1_anim = 0;
			state_interrupts = 0;
		break;
	}

	if(current_level == 0){
		SpriteManagerAdd(SpriteMoon, 0, 56);
	}


}

void UPDATE() {

	if(pdeath_counter == 1){
		if(--pdeath_counter2 == 0){
			pdeath_counter2 = 0;
			pdeath_counter = 0;
			SetState(current_state);
		}
	}

	
	if(--stage1_counter == 0){
		stage1_anim = stage1_anim == 1 ? 0 : 1;
		if(stage1_anim == 0){
			Spike_anim(&spikesAnimSt1, 112, BANK(spikesAnimSt1));
		}else{
			Spike_anim(&spikesAnim2St1, 112, BANK(spikesAnim2St1));
		}
		stage1_counter = 5;
	}
}
