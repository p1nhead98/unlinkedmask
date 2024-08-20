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
#include "WinController.h"

extern UINT8 state_interrupts;
extern UINT8 start_screen;
extern UINT8 dialog_pos;

extern UINT8 current_level;

UINT8 max_life = 2;
UINT8 current_life = 2;

UINT8 deaths_u_count = 0;
UINT8 deaths_d_count = 0;

IMPORT_TILES(pauseTiles);
IMPORT_MAP(pauseNmMap);
IMPORT_TILES(pauseTiles2);
IMPORT_MAP(pauseCmMap);

IMPORT_MAP(window);


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

void RefreshLifePause() BANKED
{

    const UINT8 heart_tiles_up[] = {75, 76, 75, 76, 75, 76};
    const UINT8 heart_tiles_down[] = {89, 90, 89, 90, 89, 90};
    const UINT8 empty_heart_tiles_up[] = {132, 134, 132, 134, 132, 134};
    const UINT8 empty_heart_tiles_down[] = {133, 135, 133, 135, 133, 135};

    const UINT8 heart_tiles_up2[] = {77, 78, 77, 78, 77, 78};
    const UINT8 heart_tiles_down2[] = {91, 92, 91, 92, 91, 92};
    const UINT8 empty_heart_tiles_up2[] = {135, 136, 135, 136, 135, 136};
    const UINT8 empty_heart_tiles_down2[] = {137, 138, 137, 138, 137, 138};

    const UINT8 end_heart_tile1  = 77;
    const UINT8 end_heart_tile2 = 91;

    const UINT8 end_heart_tile3  = 79;
    const UINT8 end_heart_tile4 = 93;
    
    UINT8 i = 0;
    UINT8 last_tile = 0;

    last_tile = (current_life + 1) / 2;
    
    for (i = 0; i != (max_life * 2); ++i)
    {
      
        set_win_tiles(12 + i, 7, 1, 1, current_level > 12 ? &empty_heart_tiles_up2[i] : &empty_heart_tiles_up[i]   );
        set_win_tiles(12 + i, 8, 1, 1, current_level > 12 ? &empty_heart_tiles_down2[i] : &empty_heart_tiles_down[i] );
    }
  
    for (i = 0; i != (current_life * 2); ++i)
    {
      
        set_win_tiles(12 + i, 7, 1, 1, current_level > 12 ? &heart_tiles_up2[i] : &heart_tiles_up[i] );
        set_win_tiles(12 + i, 8, 1, 1, current_level > 12 ? &heart_tiles_down2[i] : &heart_tiles_down[i] );
        

    }
    if(current_level > 12){
        set_win_tiles((max_life * 2) + 12, 7, 1, 1,  &end_heart_tile3 );
        set_win_tiles((max_life * 2) + 12, 8, 1, 1,  &end_heart_tile4 ); 
    }else{
        set_win_tiles((max_life * 2) + 12, 7, 1, 1,  &end_heart_tile1 );
        set_win_tiles((max_life * 2) + 12, 8, 1, 1,  &end_heart_tile2 );   
    }
   

    PRINT_POS( 13, 5 );
    if(deaths_u_count < 10){
        Printf("x %d0%u", deaths_d_count, deaths_u_count);
    }else{
        Printf("x %d%u", deaths_d_count, deaths_u_count);
    }
    
}

void cleanWindow(struct MapInfo *map, UINT8 map_bank) __nonbanked{
    CRITICAL{
        PUSH_BANK(map_bank);
            set_win_tiles(0, 0, 20, 18, map->data);
        POP_BANK;
    }
}

void SetHudWin( UINT8 on) BANKED{
    if(on == 1){
        
        cleanWindow(&window, BANK(window));
        SetWindowY(128);
        // state_interrupts = 0;
        RefreshLife();
    }else{
        
        cleanWindow(&window, BANK(window));
        SetWindowY(144);
        // LYC_REG = 0;
        // WY_REG = 128; 
        // state_interrupts = 0;
        
    }
}

void SetPauseTiles( struct MapInfo *map, UINT8 map_bank, UINT8 tiles_amount, UINT8 isPause) __nonbanked{
	UINT8 tiles_banks;
	struct TilesInfo* tiles;
    CRITICAL{
	PUSH_BANK(map_bank)
		tiles_banks = map->tiles_bank;
		tiles = map->tiles;
	POP_BANK;


        PUSH_BANK( tiles_banks);
            set_bkg_data(0, tiles_amount, tiles->data);
        POP_BANK;
        if(isPause == 1){
            PUSH_BANK(map_bank);
                set_win_tiles(0, 0, 20, 18, map->data);
            POP_BANK;
        }
    }
}



void SetPauseMenu(struct MapInfo *map, UINT8 map_bank) __nonbanked
{

    if(start_screen == 1){
        DISPLAY_OFF;
    
        SetPauseTiles( current_level > 12 ? &pauseCmMap : &pauseNmMap , current_level > 12 ? BANK(pauseCmMap) : BANK(pauseNmMap), current_level > 12 ? 139 : 136 , 1);
        RefreshLifePause();
        DISPLAY_ON;
    }else{
        DISPLAY_OFF;
        SetPauseTiles(map, map_bank, 139, 0);
        // PUSH_BANK(bank);
        //     set_bkg_data(0, 139, tile->data);
        // POP_BANK;
        
        cleanWindow(&window, BANK(window));
        DISPLAY_ON;
    }
}
