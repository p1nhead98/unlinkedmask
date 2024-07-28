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
extern UINT8 current_level;

extern UINT8 door_time_btwn;
extern UINT8 door_time_btwn_start;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    data->state = 0;

    if(current_level == 30){
        THIS->x = 704;
        THIS->y = 120;
    }
    

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
            if(current_level == 24 && THIS->x > 840){
                if(CheckCollision(THIS, spr) && data->state == 0 ) {
                    door_time_btwn_start = door_time_btwn = 110;
                    SetSpriteAnim(THIS, door_cl, 0);
                    data->state = 1;
                    door_open = 1;
                    door_time = 6;
                    door_button = 0;
                    RefreshTimer();
                    SetDoorCols(1);
                    PlayFx(CHANNEL_4, 15, 0x3F, 0xF1, 0x64, 0x80);
			    }
            }else{
                if(CheckCollision(THIS, spr) && door_button == 1 && data->state == 0 ) {
                    SetSpriteAnim(THIS, door_cl, 0);
                    if(current_level == 24){
                        door_time_btwn_start = door_time_btwn = 200;
                    }
                    data->state = 1;
                    door_open = 1;
                    door_button = 0;
                    RefreshTimer();
                    SetDoorCols( 1 );
                    PlayFx(CHANNEL_4, 15, 0x3F, 0xF1, 0x64, 0x80);
			    }
            }

		}
	}
}

void DESTROY()
{
}