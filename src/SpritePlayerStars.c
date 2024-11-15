#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 player_stars_anim[] = {3, 0, 1, 2};

extern UINT8 current_cs;

void PriorityCheckStars(){
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
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;  
    SetSpriteAnim(THIS, player_stars_anim, 10);
    data->state = 1;
 
}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;  
    if(current_state == StateCutscenes){
        if(--data->state == 0){
            THIS->x++;
            data->state = 3;
        }
    }
    // THIS->x++;
    if(THIS->anim_frame == 2){
        SpriteManagerRemove(THIS_IDX);
    }
    if(current_cs == 9){
        PriorityCheckStars();
    }
}

void DESTROY()
{
}