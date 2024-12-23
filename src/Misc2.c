#include "Banks/SetAutoBank.h"
#include "Math.h"
#include "Scroll.h"
#include "TileAnimation.h"
#include "Misc2.h"

UINT8 current_level = 10;
INT8 load_next_x = 0;
UINT8 event = 0;
Sprite* player_sprite = 0;

UINT8 load_next = 0;

IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);

IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);





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


