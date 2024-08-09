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

#endif