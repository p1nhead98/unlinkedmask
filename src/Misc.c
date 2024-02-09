#include "Banks/SetAutoBank.h"
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Scroll.h"
#include "Palette.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "rand.h"
#include "TileAnimation.h"
#include "Banks/SetAutoBank.h"


#define SCREEN_TILES_W       20 // 160 >> 3 = 20
#define SCREEN_TILES_H       18 // 144 >> 3 = 18
#define SCREEN_PAD_LEFT   1
#define SCREEN_PAD_RIGHT  2
#define SCREEN_PAD_TOP    1
#define SCREEN_PAD_BOTTOM 2

#define SCREEN_TILE_REFRES_W (SCREEN_TILES_W + SCREEN_PAD_LEFT + SCREEN_PAD_RIGHT)
#define SCREEN_TILE_REFRES_H (SCREEN_TILES_H + SCREEN_PAD_TOP  + SCREEN_PAD_BOTTOM)


UINT8 max_life = 2;
UINT8 current_life = 2;
INT16 inmunity = 0;
INT8 pal_tick = 0;
UINT8 current_pal = 0;
UINT8 on_off = 0;

IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);
IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);

void RefreshLife() BANKED
{

    const UINT8 HEART_TILE  = 129;
    const UINT8 HEART_TILE2 = 130;
    const UINT8 HEART_TILE3 = 131;
    const UINT8 HEART_TILE4 = 132;
    const UINT8 EMPTY_HEART_TILE  = 125;
    const UINT8 EMPTY_HEART_TILE2 = 126;
    const UINT8 EMPTY_HEART_TILE3 = 127;
    const UINT8 EMPTY_HEART_TILE4 = 128;

    UINT8 i = 0;
    UINT8 last_tile = 0;

    // RefreshHud();
    // set_win_tiles(2, 0, 1, 1, &LIFE_ICON);
    last_tile = (current_life + 1) / 2;


    
    for (i = 0; i != (max_life * 2); ++i)
    {
        if( i % 2 == 0){
            set_win_tiles(4 + i, 0, 1, 1, &EMPTY_HEART_TILE);
            set_win_tiles(4 + i, 1, 1, 1, &EMPTY_HEART_TILE2);
        }else{
            set_win_tiles(4 + i, 0, 1, 1, &EMPTY_HEART_TILE3);
            set_win_tiles(4 + i, 1, 1, 1, &EMPTY_HEART_TILE4);
        }
        
        // set_win_tiles(3 + i, 0, 1, 1, &EMPTY_HEART_TILE2);
        // set_win_tiles(3 + i, 0, 1, 1, &EMPTY_HEART_TILE3);
        // set_win_tiles(3 + i, 0, 1, 1, &EMPTY_HEART_TILE4);
    }
   
    for (i = 0; i != (current_life * 2); ++i)
    {
        if( i % 2 == 0){
            set_win_tiles(4 + i, 0, 1, 1, &HEART_TILE);
            set_win_tiles(4 + i, 1, 1, 1, &HEART_TILE2);
        }else{
            set_win_tiles(4 + i, 0, 1, 1, &HEART_TILE3);
            set_win_tiles(4 + i, 1, 1, 1, &HEART_TILE4);
        }
    }
    // for (; i != (max_life / 2); ++i)
    // {
    //     set_win_tiles(3 + i, 0, 1, 1, &EMPTY_HEART_TILE);
    // }
    


}


void pDelay(UINT8 numloops) BANKED
{
	UINT8 i;
	for (i = 0; i < numloops; i++)
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
		pDelay(1);
		scroll_offset_y = -seismicscale;

		//scroll_offset_y=-seismicscale;
		pDelay(1);
	}

	scroll_offset_x = 0;
	scroll_offset_y = 0;
}


void JumpRandSound(BOOLEAN spin) BANKED{

    UINT8 random = rand();
    if(random % 2 == 0){
        if(!spin){
            PlayFx(CHANNEL_4, 10, 0x01, 0x29, 0x44, 0xc0);
        }else{
            PlayFx(CHANNEL_4, 15, 0x2a, 0xcd, 0x34, 0xc0);
        }
        
    }else{
        if(!spin){
            PlayFx(CHANNEL_4, 10, 0x13, 0x29, 0x42, 0xc0);
        }else{
            PlayFx(CHANNEL_4, 15, 0x2a, 0xcd, 0x33, 0xc0);  
        }
        
    }
 
}

void ScrollRelocateMapTo(UINT16 new_x, UINT16 new_y) BANKED{
    UINT8 i;
    INT16 y;

    // These are externs from scroll.h
    // Update the
    scroll_x = new_x;
    scroll_y = new_y;

    // PUSH_BANK(scroll_bank);
    y = new_y >> 3;
    for(i = 0u; i != (SCREEN_TILE_REFRES_H) && y != scroll_h; ++i, y ++) {
        ScrollUpdateRow((scroll_x >> 3) - SCREEN_PAD_LEFT,  y - SCREEN_PAD_TOP);
    }
    // POP_BANK;
}

void RefreshTimer( UINT8 timer ) BANKED{

    UINT8 i = 0;
    UINT8 x = 0;
    
    const UINT8 CLOCK_TILE  = 133;
    const UINT8 CLOCK_TILE2 = 135;
    const UINT8 CLOCK_TILE3  = 134;
    const UINT8 CLOCK_TILE4 = 136;

    const UINT8 TIME_TILE  = 137;
    const UINT8 TIME_TILE2 = 138;
    
    const UINT8 CLEAN_TILE = 0;

    if((timer) == 6){
        set_win_tiles(12, 0, 1, 1, &CLOCK_TILE);
        set_win_tiles(13, 0, 1, 1, &CLOCK_TILE2); 
        set_win_tiles(12, 1, 1, 1, &CLOCK_TILE3);
        set_win_tiles(13, 1, 1, 1, &CLOCK_TILE4); 
        for (i = 0; i != (timer ); ++i)
        {
            set_win_tiles(14 + i, 0, 1, 1, &TIME_TILE);
            set_win_tiles(14 + i, 1, 1, 1, &TIME_TILE2); 
        }
    }else if(timer > 0){
        set_win_tiles(14 + (timer) , 0, 1, 1, &CLEAN_TILE);
        set_win_tiles(14 + (timer), 1, 1, 1, &CLEAN_TILE);
    }else{
        for (i = 0; i != 8; ++i)
        { 
            set_win_tiles(12 + i, 0, 1, 1, &CLEAN_TILE);
            set_win_tiles(12 + i, 1, 1, 1, &CLEAN_TILE); 
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
			}else if(i > 19u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}
            
		}
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 60);
        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 56);
        
    }else if(onOff == 1){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 15u && i < 20u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}else if(i > 19u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}
		}

        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 60);
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 56);
    }

}

void SetDoorCols(UINT8 off) BANKED{
    if(off == 1){
        Door_Anim(&darkTileAnim, 0, BANK(darkTileAnim), 64, 1);
        // Tile_Anim(9 , 12, &doorAnim, 64, BANK(doorAnim));
        // Tile_Anim(11 , 12, &doorAnim, 66, BANK(doorAnim));
    }else{
        Door_Anim(&doorAnim, 0, BANK(doorAnim), 64, 0);
    }
     
}