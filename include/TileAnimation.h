#ifndef TILE_ANIMATION_H
#define TILE_ANIMATION_H

#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Scroll.h"

void Tile_Anim(UINT8 x, UINT8 tilesAmount, struct TilesInfo *tile, UINT8 first_tile, UINT8 bank) __nonbanked;
void Set_Bkg_Data(struct TilesInfo *tile, UINT8 tileStart, UINT8 tileAmount, UINT8 bank) __nonbanked;
void Set_Sprite_Tiles(struct TilesInfo *tile, UINT8 bank, UINT8 tile_amount, UINT8 first_tile) __nonbanked;
void Set_Bkg_tiles( struct MapInfo *map) BANKED;
// void Set_SpinChange_Tiles(struct TilesInfo *tile, UINT8 bank, UINT8 tile_amount) __nonbanked;

// void Onoff_tile_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile) __nonbanked;

#endif