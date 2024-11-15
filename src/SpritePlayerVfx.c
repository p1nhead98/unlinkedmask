#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "ZGBMain.h"
#include "Misc.h"

const UINT8 player_vfx_anim[] = {3, 0, 1, 2};

extern UINT8 start_screen;

extern UINT8 current_cs;

void PriorityCheckFx(){
    if(THIS->x < 35 && THIS->mirror == NO_MIRROR){
        THIS->mirror = NM_PRIOR;
    }else if(THIS->x > 36 && THIS->x < 160 && THIS->mirror == NM_PRIOR){
        THIS->mirror = NO_MIRROR;
    }else if(THIS->x > 161 && THIS->x < 244 && THIS->mirror == NO_MIRROR){
        THIS->mirror = NM_PRIOR;
    }else if(THIS->x > 245 && THIS->x < 369 && THIS->mirror == NM_PRIOR){
        THIS->mirror = NO_MIRROR;
    }else if(THIS->x > 370 && THIS->x < 452 && THIS->mirror == NO_MIRROR){
        THIS->mirror = NM_PRIOR;

    }else if(THIS->x > 453 && THIS->x < 577 && THIS->mirror == NM_PRIOR){
        THIS->mirror = NO_MIRROR;
    }else if(THIS->x > 578 && THIS->mirror == NO_MIRROR){
        THIS->mirror = NM_PRIOR;
    }
}

void START()
{
    CUSTOM_DATA_PFX* data = (CUSTOM_DATA_PFX*)THIS->custom_data;

    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;
    SetSpriteAnim(THIS, player_vfx_anim, 30); 
}

void UPDATE()
{
    CUSTOM_DATA_PFX* data = (CUSTOM_DATA_PFX*)THIS->custom_data;

    if(start_screen == 0){

        if(data->start == 0){
            data->start = 1;
            THIS->y = data->initial_y;
            THIS->anim_speed = data->initial_frame_speed;
        }
    
        if(THIS->anim_frame == 2){
            SpriteManagerRemove(THIS_IDX);
        }

        if(current_cs == 9){
            PriorityCheckFx();
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