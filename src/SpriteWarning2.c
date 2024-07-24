#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern INT8 door_time;
extern INT8 door_open;

const UINT8 warning_anim2[] = {6, 0, 1, 0, 1, 2, 2};



void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, warning_anim2, 20);
    data->state = 3;
    data->counter = 0;
    THIS->lim_x = 33;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if(THIS->anim_frame == 5){
        SpriteManagerRemove(THIS_IDX);
    }   
}

void DESTROY()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

    
}