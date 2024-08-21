#include "Banks/SetAutoBank.h"
#include "Math.h"
#include "Scroll.h"
#include "TileAnimation.h"
#include "Misc2.h"

UINT8 current_level = 0;
INT8 load_next_x = 0;
UINT8 event = 0;
Sprite* player_sprite = 0;

UINT8 load_next = 0;

IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);

IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);

void PerDelay(UINT8 numloops) BANKED
{
	
	for (UINT8 i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
}

void ScreenShake(UINT8 duration, INT8 seismicscale) BANKED
{

	UINT8 d;

	for (d = 0; d < duration; d++)
	{

		scroll_offset_y = seismicscale;

		///scroll_offset_y=seismicscale;
		PerDelay(1);
		scroll_offset_y = -seismicscale;

		//scroll_offset_y=-seismicscale;
		PerDelay(1);
	}

	// scroll_offset_x = 0;
	scroll_offset_y = 0;
}

void SetDoorCols(UINT8 off, UINT8 shake) BANKED{
    if(off == 1){
        Set_Bkg_Data(&darkTileAnim, 64, 12, BANK(darkTileAnim));
    }else{
        Set_Bkg_Data(&doorAnim, 64, 12, BANK(doorAnim));
		if(shake){
        	ScreenShake(1,1);
		}
    }
     
}



void SetOnOffCols(UINT8 cols[], UINT8 onOff ) BANKED{

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
   
        
        // Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 81);
        // Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 85);
        
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
   
        // Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 81);
        // Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 85);
    }

}

void SetOnOffColsEvent(UINT8 cols[], UINT8 onOff ) BANKED{

    UINT8 i = 0;
    
    if(onOff == 0){
		for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 24u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}
            
		}
        // Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 77);
		Set_Bkg_Data(&OffAnim, 77, 4, BANK(OffAnim));

        
    }else if(onOff == 1){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 24u && i < 28u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}
		}

        // Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 77);
		PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
        PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
		Set_Bkg_Data(&OnAnim, 77, 4, BANK(OnAnim));
        SpriteManagerAdd(SpriteSpinOrbEvent, 1095, 192);
    }else if (onOff == 2){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 24u && i < 29u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}else if(i > 28u){
                scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
            }
            
		}
		PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
        PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
		Set_Bkg_Data(&OffAnim, 77, 4, BANK(OffAnim));
		Set_Bkg_Data(&OnAnim, 81, 4, BANK(OnAnim));
        // Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 77);
        // Onoff_tile_anim(&OnAnim, 0, BANK(OffAnim), 81);
    }

}


void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y, struct MapInfoBanked* level_map) BANKED{

	const struct MapInfoBanked* map = &level_map[current_level];
	UINT8 map_w, map_h;
	GetMapSize(map->bank, map->map, &map_w, &map_h);

	if(tile_start_x == 0) {
		tile_start_x += 1;
	} else if(tile_start_x == map_w - 1) {
		tile_start_x -= 2;
	}

	if(tile_start_y == 0) {
		tile_start_y += 1;
	} else if(tile_start_y == map_h - 1) {
		tile_start_y -= 2;
	} else {
		tile_start_y -= 1;
	}

	if(player_sprite) {
	
			player_sprite->x = (tile_start_x << 3) + (player_sprite->x & 0x7); //x &0x7 keeps the relative offset to tile (useful when climbing stairs)
			// player_sprite->y = (tile_start_y << 3) + (player_sprite->y & 0x7);
		
	}
}




INT16 Interpole(INT16 a, INT16 b, INT16 t, INT16 max) BANKED{
	return a + (b - a) * t / max;
}






// void LoadNextScreen(UINT8 current_level, UINT8 next_level, struct MapInfoBanked map) BANKED {
// 	Sprite* player = player_sprite;
// 	INT16 scroll_start_x = scroll_x;
// 	INT16 scroll_start_y = scroll_y;
// 	INT16 player_start_x = player->x;
// 	INT16 player_start_y = player->y;
// 	UINT8 ix;
// 	UINT16 tile_start_x, tile_start_y;
// 	INT16 scroll_end_x, scroll_end_y, player_end_x, player_end_y;
// 	INT16 offset_x = 0;
// 	INT16 offset_y = 0;





// 	const struct MapInfoBanked* next_map = &map[next_level];
// 	const struct MapInfoBanked* current_map = &map[current_level];





// 	UINT8 next_level_w, next_level_h, current_level_w, current_level_h;

// 	GetMapSize(next_map->bank, next_map->map, &next_level_w, &next_level_h);
// 	GetMapSize(current_map->bank, current_map->map, &current_level_w, &current_level_h);

// 	// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);

// 		ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next == 1 ? 104 : 1, &tile_start_x, &tile_start_y);
// 		// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next_x == -1 ? 4 : 3, &tile_start_x, &tile_start_y);

// 	// ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next, &tile_start_x, &tile_start_y);

// 	wait_vbl_done();
// 	InitPlayerPos(tile_start_x, tile_start_y, map);
// 	ScrollSetMap(next_map->bank, next_map->map);
	
// 	if((tile_start_x == 0) || (tile_start_x == next_level_w - 1)) {
// 		if(tile_start_x == 0) {
// 			offset_x = current_level_w << 3;
// 			offset_x = -offset_x;
// 		} else  { // tile_start_x == levels[next_level].w - 1)
// 			offset_x = next_level_w << 3;
// 		}
// 		offset_y = (tile_start_y << 3) - (INT16)((player_start_y + (player->coll_h - 1)) & 0xFFF8);

// 		//This keeps the scroll y in the same position it was on the previous screen
// 		//scroll_y = player->y + (old_scr_y - player_start_y);
// 		// ClampScrollLimits();	
// 		// scroll_end_y = scroll_y;
// 	}
	
// 	if((tile_start_y == 0) || (tile_start_y == next_level_h - 1)) {
// 		if(tile_start_y == 0) {
// 			offset_y = current_level_h << 3;
// 			offset_y = -offset_y;
// 		} else { //(tile_start_y == levels[next_level].h - 1)
// 			offset_y = next_level_h << 3;
// 		}
// 		offset_x = (tile_start_x << 3) - (INT16)((player_start_x) & 0xFFF8);
// 	}

// 	//Adding offset_x and offset_y will convert coordinates from old screen to the new one

// 		scroll_offset_x = 0x1F & (scroll_offset_x - (offset_x >> 3));
// 		scroll_start_x += offset_x;

// 		// scroll_offset_y = 0x1F & (scroll_offset_y - (offset_y >> 3));
// 		// scroll_start_y += offset_y;
	




// 	scroll_end_x = scroll_x;
// 	scroll_end_y = scroll_y;
// 	scroll_x_vblank = scroll_x = scroll_start_x;
// 	scroll_y_vblank = scroll_y = scroll_start_y;
	

// 		player_start_x += offset_x;


// 		// player_start_y += offset_y;
	
// 	player_end_x = player->x;
// 	player_end_y = player->y;
// 	player->anim_data = 0; //Animation data is in another bank, we must remove it

// 	//Clear all sprites except the first one
// 	for(ix = 1u; ix != sprite_manager_updatables[0]; ++ix) {
// 		SpriteManagerRemove(ix);
// 	}
// 	SpriteManagerFlushRemove();

// 	//Because the way I update the scroll there are 2 columns or 1 that need to be updated first
// 	//Do this here, after settting scroll_x and scroll_y to avoid an annoying blink (because scroll_x and scroll_y are used on vblank)
// 	if(tile_start_x == 0) {
// 		ScrollUpdateColumn((scroll_end_x >> 3),       (scroll_y >> 3) - 1);
// 		ScrollUpdateColumn((scroll_end_x >> 3) + 1,   (scroll_y >> 3) - 1);
// 	} else if(tile_start_x == next_level_w - 1) {
// 		ScrollUpdateColumn((scroll_start_x >> 3) - 1, (scroll_y >> 3) - 1);
// 	}

// 	if(tile_start_y == 0) {
// 		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3));
// 		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3) + 1);
// 	}  else if(tile_start_y == next_level_h - 1) {
// 		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_start_y >> 3) - 1);
		
// 	}
	
// 	clamp_enabled = 0;
// 	for(ix = 0; ix != SCREENWIDTH; ix += 4) {
	
// 		MoveScroll(
// 			(Interpole(scroll_start_x, scroll_end_x, ix, SCREENWIDTH)) , 
// 			48
// 		);
		
// 		player->x = Interpole(player_start_x, player_end_x, ix, SCREENWIDTH);
// 		player->y = Interpole(player_start_y, player_end_y, ix, SCREENWIDTH);
// 		THIS = player;
// 		DrawSprite();
	
// 		wait_vbl_done();
// 		SwapOAMs();
// 	}
	
// 	player->x = player_end_x;
// 	player->y = player_end_y;
// 	clamp_enabled = 1;
// }