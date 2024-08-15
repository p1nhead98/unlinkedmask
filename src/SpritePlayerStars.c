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
}

void DESTROY()
{
}