#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 mini_shine_anim[] = {6, 0, 1, 0, 1, 0, 1};

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;  
    data->state = 4;
    SetSpriteAnim(THIS, mini_shine_anim, 16);

}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
  
    switch (data->state)
    {
    case 0:
        THIS->x--;
        THIS->y--;
        break;
    case 1:
        THIS->x--;
        THIS->y++;
        break;
    case 2:
        THIS->x++;
        THIS->y--;
        break;
    case 3:
        THIS->x++;
        THIS->y++;
        break;
    
   
    }  
    if(THIS->anim_frame == 5){
        SpriteManagerRemove(THIS_IDX);
    }
}

void DESTROY()
{
}