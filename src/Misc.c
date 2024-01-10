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

// void ScreenVerticalShake(UINT8 framesBtw, UINT8 seconds, UINT8 intensity) BANKED
// {
//     UINT16 initial_y = scroll_y;
//     UINT8 initialSeconds = seconds;
//     UINT8 initTime = 0;
//     UINT8 i = 0;
//     UINT8 x = 0;

//     for (i = 0; i != seconds; ++i)
//     {
//         if(scroll_y == initial_y){
//             scroll_y = scroll_y + intensity;
//         }else{
//             for (x = 0; x != framesBtw; ++x){
//                 if(x == (framesBtw -1)){
//                     scroll_y = scroll_y - intensity;
//                 }
//             }
            
//         }  
//     }
    
   
//     // if(--seconds == 0){
//     //     if(initTime != times){
        
//     //         if(initTime % 2 == 0){
//     //             scroll_y = scroll_y - intensity;
//     //         }else{
//     //             scroll_y = initial_y;
//     //         }
//     //         initTime++;
//     //         seconds = initialSeconds;
//     //     }
//     // }
// }

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
            PlayFx(CHANNEL_4, 10, 0x2a, 0xcd, 0x34, 0xc0);
        }
        
    }else{
        if(!spin){
            PlayFx(CHANNEL_4, 10, 0x13, 0x29, 0x42, 0xc0);
        }else{
            PlayFx(CHANNEL_4, 10, 0x2a, 0xcd, 0x33, 0xc0);  
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