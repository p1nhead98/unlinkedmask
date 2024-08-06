#include "Banks/SetAutoBank.h"
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Scroll.h"
#include "Palette.h"



void Tile_Anim(UINT8 x, UINT8 tilesAmount, struct TilesInfo *tile, UINT8 first_tile, UINT8 bank) __nonbanked
{
        UINT16 tileData[16];
        PUSH_BANK(bank);
        memcpy(tileData, &tile->data[16 * (x % tilesAmount)], 16);
        set_bkg_data(first_tile, 1, tileData);
        POP_BANK;
}

void Spike_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank) __nonbanked{
    
    PUSH_BANK(bank);
     set_bkg_data(tileStart, 4, tile->data);

    POP_BANK;
}


void Set_Sprite_Tiles(struct TilesInfo *tile, UINT8 bank, UINT8 tile_amount, UINT8 first_tile) __nonbanked{
    PUSH_BANK(bank);
    set_sprite_data(first_tile, tile_amount,  tile->data);
    POP_BANK;
 
}

void Set_SpinChange_Tiles(struct TilesInfo *tile, UINT8 bank, UINT8 tile_amount) __nonbanked{
   
    PUSH_BANK(bank);
    set_bkg_data(48, tile_amount, tile->data);
    POP_BANK;
}

void SetMugTiles(struct TilesInfo *tile, UINT8 bank, UINT8 init_tile) __nonbanked{
    PUSH_BANK(bank);
    Tile_Anim(init_tile, 36, tile, 247, bank);
    Tile_Anim(init_tile + 1, 36, tile, 248, bank);
    Tile_Anim(init_tile + 2, 36, tile, 249, bank);
    Tile_Anim(init_tile + 3, 36, tile, 250, bank);
    Tile_Anim(init_tile + 4, 36, tile, 251, bank);
    Tile_Anim(init_tile + 5, 36, tile, 252, bank);
    Tile_Anim(init_tile + 6, 36, tile, 253, bank);
    Tile_Anim(init_tile + 7, 36, tile, 254, bank);
    Tile_Anim(init_tile + 8, 36, tile, 255, bank);
    POP_BANK;
}

void Onoff_tile_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile) __nonbanked{
    
    PUSH_BANK(bank);
    Tile_Anim(tileStart, 12, tile, firstTile, bank);
	Tile_Anim(tileStart + 1, 12, tile, firstTile + 1, bank);
	Tile_Anim(tileStart + 2, 12, tile, firstTile + 2, bank);
	Tile_Anim(tileStart + 3, 12, tile, firstTile + 3, bank);
    POP_BANK;
}
void Door_Anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile, UINT8 off) __nonbanked{
    UINT8 i = 0;
    PUSH_BANK(bank);
    for ( i = 0; i < 12; i++)
    {
        if(off == 1){
            if(i > 2){
                Tile_Anim(tileStart + 1, 12, tile, firstTile + i, bank);
            }else{
                Tile_Anim(tileStart + i, 12, tile, firstTile + i, bank);
            }
            
        }else{
            Tile_Anim(tileStart + i, 12, tile, firstTile + i, bank);
        }
        
    }
    
 
    POP_BANK;
}


void TitleScreenAnimation(UINT8 index) BANKED{
    const UINT8 BORDER_L_1  = 0;
    const UINT8 BORDER_L_2  = 1;
    const UINT8 BORDER_L_3  = 66;
    const UINT8 BORDER_L_4  = 67;
    const UINT8 BORDER_L_5  = 68;
    const UINT8 BORDER_L_6  = 69;
    const UINT8 BORDER_L_7  = 70;
    const UINT8 BORDER_L_8  = 71;
    const UINT8 BORDER_L_9  = 72;
    const UINT8 BORDER_R_1  = 3;
    const UINT8 BORDER_R_2  = 0;
    const UINT8 BORDER_R_3  = 74;
    const UINT8 BORDER_R_4  = 73;
    const UINT8 BORDER_R_5  = 76;
    const UINT8 BORDER_R_6  = 75;
    const UINT8 BORDER_R_7  = 77;
    const UINT8 BORDER_R_8  = 78;
    const UINT8 BORDER_R_9  = 79;
    
    const UINT8 BORDER_BLACK  = 2;

    const UINT8 LETSGO[] = {56, 57, 58, 59, 60, 61, 62, 63, 64};
    const UINT8 EXCLAMATION_1 = 55; 
    const UINT8 EXCLAMATION_2 = 65;

    switch(index){
        case 0:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_1);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_2);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_1);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_2);
            }
        break;
        case 1:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_3);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_4);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_3);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_4);
            }
        break;
        case 2:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_5);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_6);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_5);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_6);
            }
        break;
        case 3:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_7);
                set_bkg_tiles(1, i, 1, 1, &BORDER_BLACK);
                set_bkg_tiles(18, i, 1, 1, &BORDER_BLACK);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_7);
            }
        break;
        case 4:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_8);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_8);
            }
        break;
        case 5:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_9);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_9);
            }
        break;
        case 7:
            for(UINT8 i = 6; i < 15 ; i++){
                set_bkg_tiles(i, 12, 1, 1, &BORDER_BLACK);
            }
            set_bkg_tiles(14, 11, 1, 1, &BORDER_BLACK);
            set_bkg_tiles(13, 13, 1, 1, &BORDER_BLACK);
            break;
        case 8:
            for(UINT8 i = 6; i < 15 ; i++){
                set_bkg_tiles(i, 12, 1, 1, &LETSGO[i - 6]);
            }
            set_bkg_tiles(14, 11, 1, 1, &EXCLAMATION_1);
            set_bkg_tiles(13, 13, 1, 1, &EXCLAMATION_2);
        break;
    }
}

// void WarningTileAnim(UINT8 x, struct TilesInfo *tile, UINT8 first_tile, UINT8 bank){


//         unsigned char tileData[16];
//         PUSH_BANK(bank);
//             memcpy(tileData, &tile->data[16 << ((x  >> 1) )], 16);
//             set_bkg_data(111, 1, tileData);
//             memcpy(tileData, &tile->data[16 << (((x >> 1) + 8u))], 16);
//             set_bkg_data(112, 1, tileData);
//             memcpy(tileData, &tile->data[16 << (((x >> 1) + 16u))], 16);
//             set_bkg_data(113, 1, tileData);
//             memcpy(tileData, &tile->data[16 << (((x >> 1) + 24u))], 16);
//             set_bkg_data(114, 1, tileData);
//         POP_BANK;
//     		// Tile_Anim(scroller_x2 >> 1, 32, &warningText1, 111, BANK(warningText1));
// 			// Tile_Anim((scroller_x2 >> 1) + 8, 32, &warningText1, 112, BANK(warningText1));
// 			// Tile_Anim((scroller_x2 >> 1) + 16, 32, &warningText1, 113, BANK(warningText1));
// 			// Tile_Anim((scroller_x2 >> 1) + 24, 32, &warningText1, 114, BANK(warningText1));
// }


// void Tile_Anim2(UINT8 x, int tilesAmount, struct TilesInfo *tile, UINT8 first_tile)
// {

//     unsigned char tileData[16];
//     PUSH_BANK(tile->bank);
//     if(x == tilesAmount){
//         x = 0;
//     }
//     set_bkg_data(first_tile, 1, &tile->data->data[x]);
//     POP_BANK;
// }
