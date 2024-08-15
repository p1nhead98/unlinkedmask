#ifndef MISC2_H
#define MISC2_H

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
void SetDoorCols(UINT8 off) BANKED;
void SetOnOffCols(UINT8 cols[], UINT8 onOff ) BANKED;

#endif