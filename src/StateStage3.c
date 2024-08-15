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

IMPORT_MAP(lvl_11);
IMPORT_MAP(lvl_12);
IMPORT_MAP(lvl_13);
IMPORT_MAP(lvl_14);
IMPORT_MAP(lvl_15);
IMPORT_MAP(lvl_16);


IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim2);
IMPORT_TILES(templeCloudAnim);
IMPORT_TILES(templeCloudAnim2);
IMPORT_TILES(templeCloudAnim3);

DECLARE_MUSIC(unlinkedinside1);

UINT8 stage3_col_tiles[] = {4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 56, 57, 58, 59, 60, 61, 62, 63, 77, 78, 79, 80, 81, 82, 83, 84, 0};

UINT8 door_sounds[] = { 0x49, 0x3F, 0x35, 0x2B, 0x21, 0x17 };

UINT8 current_stage3 = 0;
UINT8 stage3_counter = 0;
UINT8 stage3_counter_2 = 0;
UINT8 stage3_counter_3 = 0;
UINT8 stage3_counter_4 = 0;
UINT8 stage3_anim = 0;
UINT8 stage3_anim_2 = 0;
UINT8 stage3_anim_3 = 0;
UINT8 stage3_anim_4 = 0;


extern UINT8 door_time;
extern UINT8 door_time_btwn;
extern UINT8 door_time_btwn_start;
extern UINT8 door_open;
extern BOOLEAN door_button;
extern UINT8 on_off;

extern UINT8 current_level;
extern UINT8 can_scroll_x;
extern UINT8 can_scroll_y;
extern UINT8 pdeath_counter;
extern UINT8 pdeath_counter2;
extern UINT8 max_life;
extern UINT8 current_life;
extern UINT8 state_interrupts;

const struct MapInfoBanked stage3_levels[] = {
	BANKED_MAP(lvl_11),
	BANKED_MAP(lvl_12),
	BANKED_MAP(lvl_13),
	BANKED_MAP(lvl_14),
	BANKED_MAP(lvl_15),
	BANKED_MAP(lvl_16),


};

const START_POS stage3_start_positions[] = {
	{0, 144}, 
	{0, 96}, 
	{0, 112}, 
	{0, 128}, 
	{0, 96}, 
};


void START() {
	const struct MapInfoBanked* st_3_level = &stage3_levels[current_level]; 

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
	BGP_REG	 = PAL_DEF(0, 1, 2, 3); 


	can_scroll_x = 1;

	current_life = max_life;

	switch(current_level){

		case 0:
			PlayMusic(unlinkedinside1, 1);
			door_time_btwn_start = door_time_btwn = 35;

			scroll_target = SpriteManagerAdd(SpritePlayer, stage3_start_positions[current_level].start_x, stage3_start_positions[current_level].start_y);
			InitScroll(st_3_level->bank, st_3_level->map, stage3_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			stage3_counter = 3;
			stage3_anim = 0;
			state_interrupts = 0;

			// SetOnOffCols(collision_tiles2, on_off);
		break;
		default:
			
			scroll_target = SpriteManagerAdd(SpritePlayer, stage3_start_positions[current_level].start_x, stage3_start_positions[current_level].start_y);
			InitScroll(st_3_level->bank, st_3_level->map, stage3_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			stage3_counter = 3;
			stage3_anim = 0;
			state_interrupts = 0;
		break;
	}

	// if(current_level == 0){
	// 	SpriteManagerAdd(SpriteMoon, 0, 56);
	// }

	stage3_counter_2 = stage3_counter_3 = stage3_counter_4 = 1;
	stage3_anim_2 = stage3_anim_3 = stage3_anim_4 = 0;

	door_open = 0;
	door_button = 1;
	door_time = 6;

	on_off = 0;
	SetOnOffCols( stage3_col_tiles, on_off);

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

	
	if(--stage3_counter == 0){
		stage3_anim = stage3_anim == 1 ? 0 : 1;
		if(stage3_anim == 0){
			Set_Bkg_Data(&spikesAnim, 112, 4, BANK(spikesAnim));
		}else{
			Set_Bkg_Data(&spikesAnim2, 112, 4, BANK(spikesAnim2));
		}
		stage3_counter = 5;
	}



	// if(_cpu == CGB_TYPE){
		if(--stage3_counter_2 == 0){
			stage3_counter_2 = 6;
			stage3_anim_2++;
			Tile_Anim(stage3_anim_2, 8, &templeCloudAnim, 76, BANK(templeCloudAnim));
		}

		if(--stage3_counter_3 == 0){
			stage3_counter_3 = 4;
			stage3_anim_3++;
			Tile_Anim(stage3_anim_3, 8, &templeCloudAnim2, 48, BANK(templeCloudAnim2));
		}

		
		if(--stage3_counter_4 == 0){
			stage3_counter_4 = 2;
			stage3_anim_4++;
			Tile_Anim(stage3_anim_4, 8, &templeCloudAnim3, 47, BANK(templeCloudAnim3));
		}
	// }




	if(door_open == 1 && door_time_btwn > 0){
			door_time_btwn--;
		}else if(door_open == 1 ){
			door_time--;
			PlayFx(CHANNEL_1 , 10, 0x18, 0xBF, 0xF1,door_sounds[door_time], 0x87);
			RefreshTimer();
			door_time_btwn = door_time_btwn_start;
		}
		if(door_time == 0 ){
			door_open = 0;
			door_time = 6;
			door_button = 1;
			SetDoorCols(0);
			PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
		}

}
