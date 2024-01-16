#ifndef TILE_ANIMATION_H
#define TILE_ANIMATION_H

#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Scroll.h"

void Tile_Anim(UINT8 x, int tilesAmount, struct TilesInfo *tile, UINT8 first_tile, UINT8 bank) BANKED;
void Spike_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank) BANKED;
void Onoff_tile_anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile) BANKED;
void Door_Anim(struct TilesInfo *tile, UINT8 tileStart, UINT8 bank, UINT8 firstTile, UINT8 off) BANKED;
#endif