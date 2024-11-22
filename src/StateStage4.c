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

IMPORT_MAP(lvl_17);
IMPORT_MAP(lvl_18);
IMPORT_MAP(lvl_19);
IMPORT_MAP(lvl_20);

IMPORT_MAP(window3);

IMPORT_TILES(cloudAnim1);
IMPORT_TILES(cloudAnim2);
IMPORT_TILES(cloudAnim3);

IMPORT_TILES(spinChangerAnim);
IMPORT_TILES(spinChangerAnim2);

IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim2);

IMPORT_TILES(spinChangerAnim4);
IMPORT_TILES(spinChangerAnim3);


IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);

IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim3);


DECLARE_MUSIC(unlinkedrooftop);

UINT8 stage4_col_tiles[] = {4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 56, 57, 58, 59, 60, 61, 62, 63, 77, 78, 79, 80, 81, 82, 83, 84, 0};

UINT8 door_sounds2[] = { 0x49, 0x3F, 0x35, 0x2B, 0x21, 0x17 };

UINT8 stage4_cando = 0;
UINT8 stage4_counter = 0;
UINT8 stage4_counter_2 = 0;
UINT8 stage4_counter_3 = 0;
UINT8 stage4_counter_4 = 0;
UINT8 stage4_anim = 0;
UINT8 stage4_anim_2 = 0;
UINT8 stage4_anim_3 = 0;
UINT8 stage4_anim_4 = 0;
UINT8 onoff_auto_time2 = 0;


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

extern Sprite* player_sprite;
extern UINT8 load_next;
extern INT8 player_state;
extern UINT8 change_jump_count;

extern UINT8 event;
extern UINT8 current_cs;

const struct MapInfoBanked stage4_levels[] = {
	BANKED_MAP(lvl_17),
	BANKED_MAP(lvl_18),
	BANKED_MAP(lvl_19),
	BANKED_MAP(lvl_20),

};

const START_POS stage4_start_positions[] = {
	{0, 128}, 
	{0, 128}, 
	{0, 104}, 
	{0, 96}, 
	{0, 112}, 
	{0 , 104},
};

void AutomaticOnOff2(UINT8 cols[], UINT8 onOff ){
  UINT8 i = 0;

    if(onOff == 0){
		for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 15u && i < 20u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}else if(i > 19u && i < 25u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}
            
		}
  
		Set_Bkg_Data(&OffAnim, 60, 4, BANK(OffAnim));
		Set_Bkg_Data(&OnAnim, 56, 4, BANK(OnAnim));
		Set_Bkg_Data(&spikesAnim, 81, 4, BANK(spikesAnim));
		Set_Bkg_Data(&spikesAnim3, 85, 4, BANK(spikesAnim3));
        
    }else if(onOff == 1){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 15u && i < 20u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}else if(i > 19u && i < 25u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}
		}

		Set_Bkg_Data(&OnAnim, 60, 4, BANK(OnAnim));
		Set_Bkg_Data(&OffAnim, 56, 4, BANK(OffAnim));
		Set_Bkg_Data(&spikesAnim3, 81, 4, BANK(spikesAnim3));
		Set_Bkg_Data(&spikesAnim, 85, 4, BANK(spikesAnim));
    }

}


void START() {
	//current_level = 0;
	const struct MapInfoBanked* st_4_level = &stage4_levels[current_level]; 

	CRITICAL {
#ifdef CGB
	if (_cpu == CGB_TYPE) {

		TMA_REG = 129u;
			
	}else{
	
		TMA_REG = 192u;
		
	}
#else
	TMA_REG = 192u;
		
#endif
	}
	INIT_HUD(window3);

	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);
	BGP_REG	 = PAL_DEF(0, 1, 2, 3); 

	can_scroll_x = 1;

	current_life = max_life;
	change_jump_count = 0;

	switch(current_level){

		case 0:
			PlayMusic(unlinkedrooftop, 1);
			door_time_btwn_start = door_time_btwn = 95;

			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
			InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			//SetHudWin(1);
			stage4_counter = 3;
			stage4_anim = 0;
			state_interrupts = 0;

			// SetOnOffCols(collision_tiles2, on_off);
		break;

		case 1:
			door_time_btwn_start = door_time_btwn = 35;

			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
			InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			//SetHudWin(1);
			stage4_counter = 3;
			stage4_anim = 0;
			state_interrupts = 0;

			// SetOnOffCols(collision_tiles2, on_off);
		break;

		case 2:
			door_time_btwn_start = door_time_btwn = 85;

			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
			InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			//SetHudWin(1);

			on_off = 0;
			SetOnOffCols( stage4_col_tiles, on_off);

			stage4_counter = 3;
			stage4_anim = 0;
			state_interrupts = 0;

			// SetOnOffCols(collision_tiles2, on_off);
		break;

		case 3:
			door_time_btwn_start = door_time_btwn = 126;

			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
			InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
			ScrollRelocateMapTo(0,48);
			//SetHudWin(1);
			SetOnOffCols( stage4_col_tiles, on_off);

			stage4_counter = 3;
			stage4_anim = 0;
			state_interrupts = 0;

			onoff_auto_time2 = 20;
			stage4_cando = 0;
			AutomaticOnOff2(stage4_col_tiles, stage4_cando);

			// SetOnOffCols(collision_tiles2, on_off);
		break;
		// case 1:
		// 	door_time_btwn_start = door_time_btwn = 120;
		// 	player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
		// 	InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
		// 	ScrollRelocateMapTo(0,48);
		// 	//SetHudWin(1);
		// 	stage4_counter = 3;
		// 	stage4_anim = 0;
		// 	state_interrupts = 0;
		// 	break;
		// case 3:
		// 	door_time_btwn_start = door_time_btwn = 170;
		// 	player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
		// 	InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
		// 	ScrollRelocateMapTo(0,48);
		// 	//SetHudWin(1);
		// 	SetOnOffColsEvent(stage4_col_tiles, 0);
		// 	stage4_cando = event = 0;
		// 	stage4_counter = 3;
		// 	stage4_anim = 0;
		// 	state_interrupts = 0;

		// 	break;
		// case 4:
		// 	door_time_btwn_start = door_time_btwn = 220;
		// 	player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
		// 	InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
		// 	ScrollRelocateMapTo(0,48);
		// 	//SetHudWin(1);
		// 	SetOnOffColsEvent(stage4_col_tiles, 0);
		// 	stage4_counter = 3;
		// 	stage4_anim = 0;
		// 	state_interrupts = 0;
		// 	break;
		// case 5:
		// 	PlayMusic(unlinkedinside1, 1);
		// 	player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
		// 	InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
		// 	ScrollRelocateMapTo(0,48);
		// 	//SetHudWin(1);
		// 	SetOnOffColsEvent(stage4_col_tiles, 0);
		// 	stage4_counter = 3;
		// 	stage4_anim = 0;
		// 	state_interrupts = 0;
		// 	onoff_auto_time2 = 20;
		// 	stage4_cando = 0;
		// 	AutomaticOnOff2(stage4_col_tiles, stage4_cando);
		// 	break;
		// default:
			
		// 	player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, stage4_start_positions[current_level].start_x, stage4_start_positions[current_level].start_y);
		// 	InitScroll(st_4_level->bank, st_4_level->map, stage4_col_tiles, 0);
		// 	ScrollRelocateMapTo(0,48);
		// 	//SetHudWin(1);
		// 	stage4_counter = 3;
		// 	stage4_anim = 0;
		// 	state_interrupts = 0;
		// break;
	}

	// if(current_level == 0){
	// 	SpriteManagerAdd(SpriteMoon, 0, 56);
	// }
	

	
	RefreshLife();


	stage4_counter_2 = stage4_counter_3 = stage4_counter_4 = 1;
	stage4_anim_2 = stage4_anim_3 = stage4_anim_4 = 0;

	door_open = 0;
	door_button = 1;
	door_time = 6;

	on_off = 0;
	// SetOnOffCols( stage4_col_tiles, on_off);

    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

}



void ScrollFindTileInCornersSt4(UINT16 map_w, UINT16 map_h, const struct MapInfoBanked* map, UINT8 tile, UINT16* x, UINT16* y) {
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

void LoadNextScreenSt4(UINT8 current_level, UINT8 next_level) {
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





	const struct MapInfoBanked* next_map = &stage4_levels[next_level];
	const struct MapInfoBanked* current_map = &stage4_levels[current_level];





	UINT8 next_level_w, next_level_h, current_level_w, current_level_h;

	GetMapSize(next_map->bank, next_map->map, &next_level_w, &next_level_h);
	GetMapSize(current_map->bank, current_map->map, &current_level_w, &current_level_h);
	ScrollFindTileInCornersSt4(next_level_w, next_level_h, next_map, load_next == 1 ? 104 : 1, &tile_start_x, &tile_start_y);
	wait_vbl_done();
	InitPlayerPos(tile_start_x, tile_start_y, stage4_levels);
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


	if(--stage4_counter == 0){
		stage4_counter = 6;
		stage4_anim++;
		if(change_jump_count == 0){
			Tile_Anim(stage4_anim, 6, &spinChangerAnim, 47, BANK(spinChangerAnim));	
		}else{
			Tile_Anim(stage4_anim, 6, &spinChangerAnim2, 47, BANK(spinChangerAnim2));
		}
	}




		if(_cpu == CGB_TYPE){
			if(--stage4_counter_2 == 0){
				stage4_counter_2 = 5;
				stage4_anim_2++;
				if(stage4_anim_2 % 2 == 0){
					Set_Bkg_Data(&spikesAnim, 112, 4, BANK(spikesAnim));
				}else{
					Set_Bkg_Data(&spikesAnim2, 112, 4, BANK(spikesAnim2));
				}
				// Tile_Anim(stage4_anim_2, 8, &cloudAnim2, 44, BANK(cloudAnim2));
				// Tile_Anim(stage4_anim_2 + 8, 16, &cloudAnim1, 46, BANK(cloudAnim1));
			}
			if(--stage4_counter_3 == 0){
				stage4_counter_3 = 30;
				stage4_anim_3++;
				Tile_Anim(stage4_anim_3, 8, &cloudAnim3, 43, BANK(cloudAnim3));
				// Tile_Anim(stage4_anim_2 + 8, 16, &cloudAnim1, 46, BANK(cloudAnim1));
			}
		}


	if( change_jump_count > 0 ){
		if(change_jump_count == 20){
			Set_Bkg_Data(&spinChangerAnim4, 48, 8, BANK(spinChangerAnim4));
			PlayFx(CHANNEL_1, 20, 0x25, 0xbf, 0xe2, 0x40, 0x86);
		}else if(change_jump_count == 1){
			Set_Bkg_Data(&spinChangerAnim3, 48, 8, BANK(spinChangerAnim3));
		}
		change_jump_count--;
	}
	



	// if(_cpu == CGB_TYPE){

	// 	if(--stage4_counter_2 == 0){
	// 		stage4_counter_2 = 8;
	// 		stage4_anim_2++;
	// 		Tile_Anim(stage4_anim_2, 8, &templeCloudAnim, 76, BANK(templeCloudAnim));
	// 	}

	// 	if(--stage4_counter_3 == 0){
	// 		stage4_counter_3 = 4;
	// 		stage4_anim_3++;
	// 		Tile_Anim(stage4_anim_3, 8, &templeCloudAnim2, 48, BANK(templeCloudAnim2));
	// 	}

		
	// 	if(--stage4_counter_4 == 0){
	// 		stage4_counter_4 = 2;
	// 		stage4_anim_4++;
	// 		Tile_Anim(stage4_anim_4, 8, &templeCloudAnim3, 47, BANK(templeCloudAnim3));
	// 	}
	
	// }




	if(door_open == 1 && door_time_btwn > 0){
		door_time_btwn--;
	}else if(door_open == 1 ){
		door_time--;
		PlayFx(CHANNEL_1 , 10, 0x18, 0xBF, 0xF1,door_sounds2[door_time], 0x87);
		RefreshTimer();
		door_time_btwn = door_time_btwn_start;
		if(door_time == 0 ){
			door_open = 0;
			door_time = 6;
			door_button = 1;
			SetDoorCols(0, 1);
			PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
		}
	}
	

	// if(current_level == 3 && player_sprite->x > 1142 && stage4_cando == 0 && event == 0){
	// 	stage4_cando = 1;
	// 	SetOnOffColsEvent(stage4_col_tiles, 1);
	// }
	// if(event == 1 ){
	// 	can_scroll_x = 1;
	// 	event++;
	// 	SetOnOffColsEvent(stage4_col_tiles, 2);
	// }
	// if(current_level == 5){
	// 	if(--onoff_auto_time2 == 0){
	// 		if(current_level == 30){
	// 			onoff_auto_time2 = 60;
	// 		}else{
	// 			onoff_auto_time2 = 90;
	// 		}
			
	// 		stage4_cando = stage4_cando == 0 ? 1 : 0;
	// 		AutomaticOnOff2(stage4_col_tiles, stage4_cando);
	// 		PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
	// 		PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
	// 	}	
	// }

	if(current_level == 3){
		if(--onoff_auto_time2 == 0){
			onoff_auto_time2 = 90;
			stage4_cando = stage4_cando == 0 ? 1 : 0;
			AutomaticOnOff2(stage4_col_tiles, stage4_cando);
			PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
			PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
		}	
	}

	if(load_next) {
		if( load_next) { //current_level > 0 || load_next == 1 (to avoid going under 0)
			
			current_level += load_next;

			
			LoadNextScreenSt4(current_level - load_next, current_level);
		
		}

		load_next = 0;
		player_state = 1;
		door_time = 0;
		RefreshTimer();

		

		switch (current_level){
			case 0: door_time_btwn_start = door_time_btwn = 95; break;
			case 1: door_time_btwn_start = door_time_btwn = 90; break;
			case 2: door_time_btwn_start = door_time_btwn = 85; SetOnOffCols( stage4_col_tiles, on_off); break;
			case 3: 
				door_time_btwn_start = door_time_btwn = 126; 
				SetOnOffCols( stage4_col_tiles, on_off); 
				onoff_auto_time2 = 20;
				stage4_cando = 0;
				AutomaticOnOff2(stage4_col_tiles, stage4_cando);
			break;
			// case 1: door_time_btwn_start = door_time_btwn = 120; break;
			// case 3: event = stage4_cando = 0; door_time_btwn_start = door_time_btwn = 170; SetOnOffColsEvent(stage4_col_tiles, 0); break;
			// case 4: door_time_btwn_start = door_time_btwn = 150; SetOnOffColsEvent(stage4_col_tiles, 0);  break;
			// case 5:	stage4_cando = 0; onoff_auto_time2 = 20; AutomaticOnOff2(stage4_col_tiles, stage4_cando); SetOnOffColsEvent(stage4_col_tiles, 0);  break;
		}

		door_open = 0;
		door_button = 1;
		door_time = 6;
		on_off = 0;
		SetDoorCols(0, 0);
		// if(_cpu == CGB_TYPE){
		// 	SpriteManagerAdd(SpriteMoon, 0, 64);
		// 	moon_1_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
		// 	CUSTOM_DATA_BTN* data_1 = (CUSTOM_DATA_BTN*)moon_1_spr->custom_data;
		// 	data_1->state = 1;
		// 	// moon_2_spr = SpriteManagerAdd(SpriteMoon, 0, 64);
		// 	// CUSTOM_DATA_BTN* data_2 = (CUSTOM_DATA_BTN*)moon_2_spr->custom_data;
		// 	// data_2->state = 2;
		// }
		
	}	


 if(KEY_PRESSED(J_DOWN) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 0;
			current_cs = 0;
			current_state = StateStage1;
			SetState(current_state);
		}else if(KEY_PRESSED(J_LEFT) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 0;
			current_cs = 0;
			current_state = StateStage3;
			SetState(current_state);
		}else if(KEY_PRESSED(J_UP) && KEY_PRESSED(J_A) && KEY_PRESSED(J_B) && KEY_PRESSED(J_SELECT)){
		    current_level = 0;
			current_cs = 0;
			current_state = StateStage4;
			SetState(current_state);
		}
}
