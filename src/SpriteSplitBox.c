#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 anim_sbox[] = {2, 0, 1};
// const UINT8 anim_sbox2[] = {2, 1, 2};
extern UINT8 current_level;

extern UINT8 start_screen;

void START()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;
    data->state = 0;

    if(current_state == StateStage4){
        switch (current_level)
        {
        case 1:
            if(THIS->x > 586){
                THIS->x += 24;
            }
            
            break;
        
        default:
            break;
        }
    }

    if(current_level == 28 && THIS->x > 592 && THIS->x < 672){
        THIS->x = 624;
    }else if(current_level == 28 && THIS->x > 1088){
        THIS->y = 136;
    }
    if(current_level == 29 && THIS->x > 448){
        THIS->x -= 12;
    }
    if(current_level == 30){
        THIS->x = 288;
        THIS->y = 152;
    }
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
                SetSpriteAnim(THIS, anim_sbox, 20);
            break;
            case 1:
                SpriteManagerRemove(THIS_IDX);
                Sprite* jbox1 = SpriteManagerAdd(SpriteJumpBox2, THIS->x, THIS->y );
                CUSTOM_DATA_BOX* dataj1 = (CUSTOM_DATA_BOX*)jbox1->custom_data;
                Sprite* jbox2 = SpriteManagerAdd(SpriteJumpBox2, THIS->x, THIS->y );
                CUSTOM_DATA_BOX* dataj2 = (CUSTOM_DATA_BOX*)jbox2->custom_data;

                dataj1->state = 2;
                dataj2->state = 3;
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