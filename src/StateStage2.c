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

IMPORT_MAP(window);

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
extern Sprite* player_sprite;
extern UINT8 load_next;
extern INT8 player_state;
extern UINT8 current_cs;

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
	const struct MapInfoBanked* st_2_level =  &stage2_levels[current_level] ; 

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
			
			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage2_start_positions[current_level].start_x, stage2_start_positions[current_level].start_y);
			InitScroll( st_2_level->bank, st_2_level->map, stage2_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			// SetHudWin(1);
			stage2_counter = stage2_counter_2 = 3;
			
			stage2_anim = stage2_anim_2 = 0;
			state_interrupts = 0;
		break;
	}

	INIT_HUD(window);
	RefreshLife();

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



void ScrollFindTileInCornersSt2(UINT16 map_w, UINT16 map_h, const struct MapInfoBanked* map, UINT8 tile, UINT16* x, UINT16* y) {
	if(ScrollFindTile(map->bank, map->map, tile, 0, 0, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, 0, map_h - 1, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, 0, 0, 1, map_h, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, map_w - 1, 0, 1, map_h, x, y)) {
		return;
	}
}


void ClampScrollLimits();

void LoadNextScreenSt2(UINT8 current_level, UINT8 next_level) {
	Sprite* player = player_sprite;
	INT16 scroll_start_x = scroll_x;
	INT16 scroll_start_y = scroll_y;
	INT16 player_start_x = player->x;
	INT16 player_start_y = player->y;
	UINT8 ix;
	UINT16 tile_start_x, tile_start_y;
	INT16 scroll_end_x, scroll_end_y, player_end_x, player_end_y;
	INT16 offset_x = 0;
	INT16 offset_y = 0;





	const struct MapInfoBanked* next_map = &stage2_levels[next_level];
	const struct MapInfoBanked* current_map = &stage2_levels[current_level];





	UINT8 next_level_w, next_level_h, current_level_w, current_level_h;

	GetMapSize(next_map->bank, next_map->map, &next_level_w, &next_level_h);
	GetMapSize(current_map->bank, current_map->map, &current_level_w, &current_level_h);

	// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);

		ScrollFindTileInCornersSt2(next_level_w, next_level_h, next_map, load_next == 1 ? 104 : 1, &tile_start_x, &tile_start_y);
		// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next_x == -1 ? 4 : 3, &tile_start_x, &tile_start_y);

	// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next, &tile_start_x, &tile_start_y);

	wait_vbl_done();
	InitPlayerPos(tile_start_x, tile_start_y, stage2_levels);
	ScrollSetMap(next_map->bank, next_map->map);
	
	if((tile_start_x == 0) || (tile_start_x == next_level_w - 1)) {
		if(tile_start_x == 0) {
			offset_x = current_level_w << 3;
			offset_x = -offset_x;
		} else  { // tile_start_x == levels[next_level].w - 1)
			offset_x = next_level_w << 3;
		}
		offset_y = (tile_start_y << 3) - (INT16)((player_start_y + (player->coll_h - 1)) & 0xFFF8);

		//This keeps the scroll y in the same position it was on the previous screen
		//scroll_y = player->y + (old_scr_y - player_start_y);
		// ClampScrollLimits();	
		// scroll_end_y = scroll_y;
	}
	
	if((tile_start_y == 0) || (tile_start_y == next_level_h - 1)) {
		if(tile_start_y == 0) {
			offset_y = current_level_h << 3;
			offset_y = -offset_y;
		} else { //(tile_start_y == levels[next_level].h - 1)
			offset_y = next_level_h << 3;
		}
		offset_x = (tile_start_x << 3) - (INT16)((player_start_x) & 0xFFF8);
	}

	//Adding offset_x and offset_y will convert coordinates from old screen to the new one

		scroll_offset_x = 0x1F & (scroll_offset_x - (offset_x >> 3));
		scroll_start_x += offset_x;

		// scroll_offset_y = 0x1F & (scroll_offset_y - (offset_y >> 3));
		// scroll_start_y += offset_y;
	




	scroll_end_x = scroll_x;
	scroll_end_y = scroll_y;
	scroll_x_vblank = scroll_x = scroll_start_x;
	scroll_y_vblank = scroll_y = scroll_start_y;
	

		player_start_x += offset_x;


		// player_start_y += offset_y;
	
	player_end_x = player->x;
	player_end_y = player->y;
	player->anim_data = 0; //Animation data is in another bank, we must remove it

	//Clear all sprites except the first one
	for(ix = 1u; ix != sprite_manager_updatables[0]; ++ix) {
		SpriteManagerRemove(ix);
	}
	SpriteManagerFlushRemove();

	//Because the way I update the scroll there are 2 columns or 1 that need to be updated first
	//Do this here, after settting scroll_x and scroll_y to avoid an annoying blink (because scroll_x and scroll_y are used on vblank)
	if(tile_start_x == 0) {
		ScrollUpdateColumn((scroll_end_x >> 3),       (scroll_y >> 3) - 1);
		ScrollUpdateColumn((scroll_end_x >> 3) + 1,   (scroll_y >> 3) - 1);
	} else if(tile_start_x == next_level_w - 1) {
		ScrollUpdateColumn((scroll_start_x >> 3) - 1, (scroll_y >> 3) - 1);
	}

	if(tile_start_y == 0) {
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3));
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3) + 1);
	}  else if(tile_start_y == next_level_h - 1) {
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_start_y >> 3) - 1);
		
	}
	
	clamp_enabled = 0;
	for(ix = 0; ix != SCREENWIDTH; ix += 4) {
	
		MoveScroll(
			(Interpole(scroll_start_x, scroll_end_x, ix, SCREENWIDTH)) , 
			48
		);
		
		player->x = Interpole(player_start_x, player_end_x, ix, SCREENWIDTH);
		player->y = Interpole(player_start_y, player_end_y, ix, SCREENWIDTH);
		THIS = player;
		DrawSprite();
	
		wait_vbl_done();
		SwapOAMs();
	}
	
	player->x = player_end_x;
	player->y = player_end_y;
	clamp_enabled = 1;
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
		
	if(load_next) {
		if( load_next) { //current_level > 0 || load_next == 1 (to avoid going under 0)
			
			current_level += load_next;

			
			LoadNextScreenSt2(current_level - load_next, current_level);
		
		}
		load_next = 0;
		player_state = 1;
		if(_cpu == CGB_TYPE){
			SpriteManagerAdd(SpriteMoon, 0, 64);
			moon_1_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
			CUSTOM_DATA_BTN* data_1 = (CUSTOM_DATA_BTN*)moon_1_spr->custom_data;
			data_1->state = 1;
			// moon_2_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
			// CUSTOM_DATA_BTN* data_2 = (CUSTOM_DATA_BTN*)moon_2_spr->custom_data;
			// data_2->state = 2;
		}
		
	}

	if(KEY_PRESSED(J_DOWN) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 0;
			current_cs = 0;
			current_state = StateTitleScreen;
			SetState(current_state);
		}else if(KEY_PRESSED(J_LEFT) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 0;
			current_cs = 0;
			current_state = StateStage1;
			SetState(current_state);
		}else if(KEY_PRESSED(J_UP) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 8;
			current_cs = 8;
			current_state = StateCutscenes;
			SetState(current_state);
		}

}
