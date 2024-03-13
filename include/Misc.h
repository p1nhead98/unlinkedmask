#ifndef MISC_H
#define MISC_H

#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Banks/SetAutoBank.h"
#include "Scroll.h"
#include "Palette.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"


// typedef struct {
// 	INT16 accel_y;
// 	INT16 accel_x;
// 	INT8 state;
// 	INT8 life;
// 	UINT8 collision;
// 	UINT8 counter;
// 	UINT16 initial_x;
// 	UINT16 initial_y;
// } CUSTOM_DATA;

typedef struct {
	INT8 state;
	INT8 start;
	UINT8 initial_frame_speed;
	UINT8 initial_y;
	UINT8 can_change;
} CUSTOM_DATA_BOX;

typedef struct {
	UINT8 state;
	UINT8 initial_state;
	UINT8 speed;
	UINT8 initial_speed;
	UINT8 initial_frame_speed;
	UINT8 initial_y;
	INT8 start;
} CUSTOM_DATA_ORB;

typedef struct {
	UINT8 state;
} CUSTOM_DATA_BTN;

typedef struct {
	UINT8 initial_frame_speed;
	UINT8 initial_y;
	INT8 start;
} CUSTOM_DATA_PFX;



void RefreshLife() BANKED;
void pDelay(UINT8 numloops) BANKED;
void ScreenShake(UINT8 duration, INT8 seismicscale) BANKED;
void JumpRandSound(BOOLEAN spin) BANKED;
void ScrollRelocateMapTo(UINT16 new_x, UINT16 new_y) BANKED;
void RefreshTimer( UINT8 timer ) BANKED;
void SetOnOffCols(UINT8 cols[], UINT8 onOff ) BANKED;
void SetDoorCols(UINT8 off) BANKED;
void SetPauseMenu() BANKED;
void cleanWindow() BANKED;
void SetOnOffColsEvent(UINT8 cols[], UINT8 onOff ) BANKED;


#endif