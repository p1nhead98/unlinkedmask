#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 crystal_attack_anim[] = {2, 0, 1};

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;    
    data->state = 0;
    SetSpriteAnim(THIS, crystal_attack_anim, 20);

}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    switch (data->state)
    {
    case 1:
        THIS->x+=2;
        if(THIS->x > 136){
            SpriteManagerRemove(THIS_IDX);
        }        
        break;
    
    case 2:
        THIS->x-=2;
        if(THIS->x < 17){
            SpriteManagerRemove(THIS_IDX);
        }
        break;
    }

}

void DESTROY()
{
}