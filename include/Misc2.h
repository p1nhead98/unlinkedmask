#ifndef MISC2_H
#define MISC2_H

#include "Banks/SetAutoBank.h"

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

typedef struct {
    UINT16 start_x;
    UINT16 start_y;
} START_POS;

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

void PerDelay(UINT8 numloops) BANKED;
void ScreenShake(UINT8 duration, INT8 seismicscale) BANKED;
void SetDoorCols(UINT8 off, UINT8 shake) BANKED;
void SetOnOffColsEvent(UINT8 cols[], UINT8 onOff ) BANKED;

void SetOnOffCols(UINT8 cols[], UINT8 onOff ) BANKED;
void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y, struct MapInfoBanked* level_map) BANKED;
INT16 Interpole(INT16 a, INT16 b, INT16 t, INT16 max) BANKED;

// void LoadNextScreen(UINT8 current_level, UINT8 next_level, struct MapInfoBanked* map) BANKED;

#endif