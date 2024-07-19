#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern UINT8 door_time;
extern UINT8 door_open;

const UINT8 fire1anim[] = {3, 0, 1, 2};
const UINT8 fire2anim[] = {4, 3, 4, 5, 6};



void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->state = 0;
    data->counter = 20;
    SetSpriteAnim(THIS, fire1anim, 16);
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch (data->state)
    {
    case 0:
        if(TranslateSprite(THIS, 0, 4)){
            data->state++;
        }
        break;
    case 1:
        if(--data->counter == 0){
            SetSpriteAnim(THIS, fire2anim, 16);
            data->state++;
        }
        break;
    case 2:
        if(THIS->anim_frame == 3){
            SpriteManagerRemove(THIS_IDX);    
        }
        
        break;
    default:
        break;
    }
    
     
}

void DESTROY()
{
}