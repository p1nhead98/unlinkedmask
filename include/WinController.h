#ifndef WIN_CONTROLLER_H
#define WIN_CONTROLLER_H

#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"


void RefreshLife() BANKED;
void RefreshLifePause() BANKED;
void cleanWindow() BANKED;
void SetHudWin( UINT8 on) BANKED;

// void SetPauseTiles( struct MapInfo *map, UINT8 map_bank, UINT8 tiles_amount , UINT8 isPause) __nonbanked;
// void SetPauseMenu(struct MapInfo *map, UINT8 map_bank) __nonbanked;
#endif