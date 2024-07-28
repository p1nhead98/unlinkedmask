#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 kaizo_anim[] = {2, 0, 0};
const UINT8 kaizo_anim2[] = {2, 1, 1};


extern UINT8 start_screen;

void START()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    data->initial_frame_speed = 0;
    data->initial_y = THIS->y = 136;
    data->initial_x = THIS->x = 1392;
    data->start = 1;
    
    SetSpriteAnim(THIS, kaizo_anim, 20);
    
    data->state = 0;
    data->can_change = 0;
}

void UPDATE()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;
    if(start_screen == 0){

        if(data->start == 0){
            data->start = 1;
            THIS->y = data->initial_y;
            THIS->anim_speed = data->initial_frame_speed;
        }
        switch(data->state){
            case 1:
                SetSpriteAnim(THIS, kaizo_anim2, 15);
                THIS->y -= 5;
                data->state++;
                
            break;
            case 2:
                if(THIS->anim_frame == 1){
                    THIS->y += 5;
                    data->state = 0;
                }
            break;
        }

    }else{
        if(THIS->y != 0  && data->start == 1){
            data->start = 0;
            data->initial_y = THIS->y;
            THIS->y = 0;
            data->initial_frame_speed = THIS->anim_speed;
            THIS->anim_speed =0;
        } 
    }
}

void DESTROY()
{
}