#ifndef CINEMATICAS_H
#define CINEMATICAS_H


#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Scroll.h"

void SetBkg(struct TilesInfo *tile, UINT8 bank,UINT8 bank2, struct MapInfo *map, UINT8 tiles_amount) __nonbanked;
void CapeCutsAnim(UINT8 current_frame) BANKED;
#endif