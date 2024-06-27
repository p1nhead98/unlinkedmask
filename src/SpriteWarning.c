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

const UINT8 warning_anim[] = {2, 0, 1, };
extern Sprite* warning_spr;
extern Sprite* warning_spr2;


void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, warning_anim, 20);
    data->state = 3;
    THIS->lim_x = 33;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch(data->state){
        case 0:
            THIS->x-=3;
            break;
        case 1:
            THIS->x+=3;
            break;
    }
}

void DESTROY()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
        warning_spr = 0;
        warning_spr2 = 0;
    
}