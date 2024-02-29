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

extern UINT8 start_screen;

extern UINT8 original_lvl_bank;
extern struct TilesInfo* original_tiles;


IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);
IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);
IMPORT_TILES(pauseTiles);
IMPORT_TILES(tiles);


void cleanWindow() BANKED{
    const UINT8 WHITETILE  = 0;
    for (UINT8 i = 0; i != 20; ++i)
        {
            set_win_tiles(0 + i, 0, 1, 1,  &WHITETILE);
            set_win_tiles(0 + i, 1, 1, 1,  &WHITETILE);
          
        }
}
void SetPauseMenu() BANKED
{

    if(start_screen == 1){
        const UINT8 col1[] = { 0, 1, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 2, 2, 2, 2 , 10, 11};
        const UINT8 col2[] = { 12, 13, 13, 13, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 21, 21, 22};
        const UINT8 col3[] = { 23, 13, 24, 25, 26, 27, 28, 29, 30, 31, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col4[] = { 23, 13, 33, 34, 35, 36, 37, 38, 39, 40, 21, 41, 42, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col5[] = { 23, 13, 43, 44, 45, 46, 47, 48, 30, 49, 21, 50, 51, 52, 21, 21, 21, 21, 21, 32};
        const UINT8 col6[] = { 23, 13, 54, 55, 56, 57, 58, 59, 60, 40, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col7[] = { 23, 61, 62, 63, 64, 65, 66, 67, 68, 69, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col8[] = { 23, 74, 75, 76, 77, 78, 79, 80, 81, 82, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col9[] = { 23, 87, 88, 89, 90, 91, 92, 93, 94, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col10[] = { 23, 95, 96, 97, 98, 21, 21, 99, 100, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col11[] = { 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 103};
        const UINT8 col12[] = { 23, 21, 21, 21, 21, 21, 21,21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col13[] = { 23, 21, 21, 21, 21, 104, 105, 106, 107, 108, 109, 110, 111, 105, 112, 21, 21, 21, 21, 32};
        const UINT8 col14[] = { 23, 21, 21, 21, 21, 21, 21,21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col15[] = { 23, 21, 21, 104, 105, 105, 113, 114, 115, 116, 117, 118, 119, 120, 105, 105, 112, 21, 21, 32};
        const UINT8 col16[] = { 23, 21, 21, 21, 21, 21, 21,21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32};
        const UINT8 col17[] = { 121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123};
        const UINT8 col18[] = { 124, 125, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 126, 127};
        DISPLAY_OFF;
        Set_Start_Tiles(&pauseTiles, BANK(pauseTiles), 128);
        
        for (UINT8 i = 0; i != 20; ++i)
        {
            set_win_tiles(0 + i, 0, 1, 1,  &col1[i]);
            set_win_tiles(0 + i, 1, 1, 1,  &col2[i]);
            set_win_tiles(0 + i, 2, 1, 1,  &col3[i]);
            set_win_tiles(0 + i, 3, 1, 1,  &col4[i]);
            set_win_tiles(0 + i, 4, 1, 1,  &col5[i]);

            set_win_tiles(0 + i, 5, 1, 1,  &col6[i]);
            set_win_tiles(0 + i, 6, 1, 1,  &col7[i]);
            set_win_tiles(0 + i, 7, 1, 1,  &col8[i]);
            set_win_tiles(0 + i, 8, 1, 1,  &col9[i]);
            set_win_tiles(0 + i, 9, 1, 1,  &col10[i]);

            set_win_tiles(0 + i, 10, 1, 1,  &col11[i]);
            set_win_tiles(0 + i, 11, 1, 1,  &col12[i]);
            set_win_tiles(0 + i, 12, 1, 1,  &col13[i]);
            set_win_tiles(0 + i, 13, 1, 1,  &col14[i]);
            set_win_tiles(0 + i, 14, 1, 1,  &col15[i]);
            set_win_tiles(0 + i, 15, 1, 1,  &col16[i]);

            set_win_tiles(0 + i, 16, 1, 1,  &col17[i]);
            set_win_tiles(0 + i, 17, 1, 1,  &col18[i]);
        }
        DISPLAY_ON;
    }else{
        DISPLAY_OFF;
        Set_Start_Tiles(&tiles, BANK(tiles), 128);
        cleanWindow();
        DISPLAY_ON;
    }
}

void RefreshLife() BANKED
{

    const UINT8 face_tiles_up[] = { 117, 119, 121, 123 };
    const UINT8 face_tiles_down[] = { 118, 120, 122, 124 };

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

    last_tile = (current_life + 1) / 2;

    for (i = 0; i != 4; ++i)
    {
        set_win_tiles(0 + i, 0, 1, 1,  &face_tiles_up[i]);
        set_win_tiles(0 + i, 1, 1, 1,  &face_tiles_down[i]);
    }

    
    for (i = 0; i != (max_life * 2); ++i)
    {
        if( i % 2 == 0){
            set_win_tiles(4 + i, 0, 1, 1, &EMPTY_HEART_TILE);
            set_win_tiles(4 + i, 1, 1, 1, &EMPTY_HEART_TILE2);
        }else{
            set_win_tiles(4 + i, 0, 1, 1, &EMPTY_HEART_TILE3);
            set_win_tiles(4 + i, 1, 1, 1, &EMPTY_HEART_TILE4);
        }
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
    // for(i = 0u; i != (SCREEN_TILE_REFRES_H) && y != scroll_h; ++i, y ++) {
    //     ScrollUpdateRow((scroll_x >> 3) - SCREEN_PAD_LEFT,  y - SCREEN_PAD_TOP);
    // }
    for (UINT8 y = 0; y < 7; y++)
	{
		for (UINT8 x = 0; x < 32; x++)
		{
				ScrollUpdateColumn(x, y);
		}
			
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