
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Scroll.h"
#include "Palette.h"



void Tile_Anim(UINT8 x, int tilesAmount, struct TilesInfo *tile, UINT8 first_tile, UINT8 bank) BANKED
{

    unsigned char tileData[16];
    PUSH_BANK(bank);
    memcpy(tileData, &tile->data[16 * (x % tilesAmount)], 16);
    set_bkg_data(first_tile, 1, tileData);
    POP_BANK;
}


void Spike_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank) BANKED{
    unsigned char tileData[16];
    PUSH_BANK(bank);
    Tile_Anim(tileStart, 12, tile, 126, bank);
	Tile_Anim(tileStart + 1, 12, tile, 127, bank);
	Tile_Anim(tileStart + 2, 12, tile, 124, bank);
	Tile_Anim(tileStart + 3, 12, tile, 125, bank);
    POP_BANK;
}

void Onoff_tile_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile) BANKED{
    
    PUSH_BANK(bank);
    Tile_Anim(tileStart, 12, tile, firstTile, bank);
	Tile_Anim(tileStart + 1, 12, tile, firstTile + 1, bank);
	Tile_Anim(tileStart + 2, 12, tile, firstTile + 2, bank);
	Tile_Anim(tileStart + 3, 12, tile, firstTile + 3, bank);
    POP_BANK;
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
