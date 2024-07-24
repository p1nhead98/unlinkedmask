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
#include "Print.h"
#include "Math.h"

#define SCREEN_TILES_W       20 // 160 >> 3 = 20
#define SCREEN_TILES_H       18 // 144 >> 3 = 18
#define SCREEN_PAD_LEFT   1
#define SCREEN_PAD_RIGHT  2
#define SCREEN_PAD_TOP    1
#define SCREEN_PAD_BOTTOM 2

#define SCREEN_TILE_REFRES_W (SCREEN_TILES_W + SCREEN_PAD_LEFT + SCREEN_PAD_RIGHT)
#define SCREEN_TILE_REFRES_H (SCREEN_TILES_H + SCREEN_PAD_TOP  + SCREEN_PAD_BOTTOM)



INT16 inmunity = 0;
INT8 pal_tick = 0;
UINT8 current_pal = 0;
UINT8 on_off = 0;

extern UINT8 start_screen;

extern UINT8 original_lvl_bank;
extern struct TilesInfo* original_tiles;

UINT8 door_time = 0;
UINT8 door_time_btwn = 0;
UINT8 door_time_btwn_start = 0;
UINT8 door_open = 0;
BOOLEAN door_button = 0;

IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);
IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);

IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim3);



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
void FillDoorCinem() BANKED{
    for (UINT8 y = 0u; y < 12u; y++)
	{
		for (UINT8 x = 0u; x < 20u; x++)
		{
				ScrollUpdateColumn(x, y);
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

void RefreshTimer() BANKED{    
    const UINT8 CLOCK_TILE  = 133;
    const UINT8 CLOCK_TILE2 = 135;
    const UINT8 CLOCK_TILE3  = 134;
    const UINT8 CLOCK_TILE4 = 136;

    const UINT8 TIME_TILE  = 137;
    const UINT8 TIME_TILE2 = 138;
    
    const UINT8 CLEAN_TILE = 0;


    if(door_time > 0){
        set_win_tiles(12, 0, 1, 1, &CLOCK_TILE);
        set_win_tiles(13, 0, 1, 1, &CLOCK_TILE2); 
        set_win_tiles(12, 1, 1, 1, &CLOCK_TILE3);
        set_win_tiles(13, 1, 1, 1, &CLOCK_TILE4); 
        for (INT8 i = 0; i != (door_time ); ++i)
        {
            set_win_tiles(14 + i, 0, 1, 1, &TIME_TILE);
            set_win_tiles(14 + i, 1, 1, 1, &TIME_TILE2); 
        }
        set_win_tiles(14 + (door_time) , 0, 1, 1, &CLEAN_TILE);
        set_win_tiles(14 + (door_time), 1, 1, 1, &CLEAN_TILE);
    }else{
        for (INT8 i = 0; i != 8; ++i)
        { 
            set_win_tiles(12 + i, 0, 1, 1, &CLEAN_TILE);
            set_win_tiles(12 + i, 1, 1, 1, &CLEAN_TILE); 
        }
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
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 77);
       
        
    }else if(onOff == 1){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 24u && i < 28u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}
		}

        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 77);
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
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 77);
        Onoff_tile_anim(&OnAnim, 0, BANK(OffAnim), 81);
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
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 60);
        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 56);
        
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

        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 60);
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 56);
    }

}

void SetDoorCols(UINT8 off) BANKED{
    if(off == 1){
        Door_Anim(&darkTileAnim, 0, BANK(darkTileAnim), 64, 1);
        PlayFx(CHANNEL_4, 15, 0x3F, 0xF1, 0x64, 0x80);
        // Tile_Anim(9 , 12, &doorAnim, 64, BANK(doorAnim));
        // Tile_Anim(11 , 12, &doorAnim, 66, BANK(doorAnim));
    }else{
        Door_Anim(&doorAnim, 0, BANK(doorAnim), 64, 0);
        ScreenShake(1,1);
        PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
    }
     
}
void AutomaticOnOff(UINT8 cols[], UINT8 onOff ) BANKED{
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
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 60);
        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 56);
        Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 81);
        Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 85);
        
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

        Onoff_tile_anim(&OnAnim, 0, BANK(OnAnim), 60);
        Onoff_tile_anim(&OffAnim, 0, BANK(OffAnim), 56);
        Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 81);
        Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 85);
    }

}

void TextWithDelay(const char* txt) BANKED{
    UINT8 i = 0;
    char* name = "Dragon";
    char char_ptr = name[2];
    PRINT(i, 0, char_ptr);
    for(i = 0u; i < 5; ++i) {
        //char_ptr = &name[i];
        //PRINT(i, 0, "A");
        pDelay(10);
	}
}

void FadeDMGCustom(UINT8 fadeout) BANKED {
	
	UINT8 pals3[] = {0, 1, 2, 3};
    UINT8 pals2[] = {0, 0, 1, 2};
    UINT8 pals1[] = {0, 0, 0, 1};
	BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, pals1[fadeout], pals2[fadeout], pals3[fadeout] );
		
}

void FadeColor() BANKED{
    FadeDMGCustom(3);
    pDelay(20);
    FadeDMGCustom(2);
    pDelay(20);
    FadeDMGCustom(1);
    pDelay(20);
    FadeDMGCustom(0);
    pDelay(20);
}

void FadeInColor() BANKED{
    FadeDMGCustom(0);
    pDelay(20);
    FadeDMGCustom(1);
    pDelay(20);
    FadeDMGCustom(2);
    pDelay(20);
    FadeDMGCustom(3);
}

void FadeCapeCuts() BANKED{
    FadeDMGCustom(0);
    SHOW_WIN;
    pDelay(30);
    FadeDMGCustom(1);
    pDelay(30);
    FadeDMGCustom(2);
    pDelay(30);
    FadeDMGCustom(3);
    pDelay(30);
}
void FadeColorAndMusic() BANKED{
    FadeDMGCustom(3);
    pDelay(20);
    NR50_REG = 0x55;
    FadeDMGCustom(2);
    pDelay(20);
    NR50_REG = 0x33;
    FadeDMGCustom(1);
    pDelay(20);
    NR50_REG = 0x11;
    FadeDMGCustom(0);
    pDelay(20);
    NR50_REG = 0x0;
    StopMusic;
}

void FadeMusic(UINT8 pointer) BANKED{
    UINT8 volume[] = {0x55,  0x33, 0x11, 0x0}; 
    NR50_REG = volume[pointer];
    if (pointer == 3)
    {
        StopMusic;
    }
    
}
// void SetDialogFace(UINT8 face) BANKED {
//     switch (face)
//     {
//     case 0: //VIEWER
        
//         break;
    
//     case 1: ///ORB??
        
//         break;
// }
