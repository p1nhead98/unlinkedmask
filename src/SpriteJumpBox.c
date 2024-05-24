#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 anim_box[] = {2, 0, 1};
const UINT8 anim_box2[] = {2, 2, 2};


extern UINT8 start_screen;

void START()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->initial_x = THIS->x;
    data->start = 1;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    data->state = 0;
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

        switch( data->state ){
            case 0:
                SetSpriteAnim(THIS, anim_box, 20);
            break;
            case 1:
        
                    SetSpriteAnim(THIS, anim_box2, 2);
                if(THIS->anim_frame == 1){
                    data->state = 0;
                    SetSpriteAnim(THIS, anim_box, 20);
                
                }
            break;
            case 2:
                if(THIS->x < (data->initial_x + 30)){
                    THIS->x+=2;
                }else{
                    data->state = 0;
                }
            break;
            case 3:
                if(THIS->x > (data->initial_x - 31)){
                    THIS->x-=2;
                }else{
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