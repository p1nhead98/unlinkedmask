#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 door_op[] = {1, 0};
const UINT8 door_cl[] = {1, 1};

extern UINT8 door_time;
extern UINT8 door_open;
extern UINT8 door_button;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    switch(data->state){
        case 0:
            SetSpriteAnim(THIS, door_op, 0);

        break;
        case 1:
                
            if(door_button == 1){
                data->state = 0;
               
            }
        break;

    }

    SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpritePlayer ) {
			if(CheckCollision(THIS, spr) && door_button == 1 && data->state == 0 ) {
                SetSpriteAnim(THIS, door_cl, 0);
                data->state = 1;
                door_open = 1;
                door_button = 0;
                RefreshTimer(door_time);
                SetDoorCols( 1 );
			}
		}
	}
}

void DESTROY()
{
}