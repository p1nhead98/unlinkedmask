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

const UINT8 skull_flame_anim[] = {3, 0, 1, 2};
extern Sprite* bossSkullFlame_spr1;
extern Sprite* bossSkullFlame_spr2;

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, skull_flame_anim, 20);
    data->state = 0;

}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch(data->state){
        case 0:
            THIS->x--;
            break;
        case 1:
            THIS->x++;
            break;
    }
}

void DESTROY()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if(data->state == 0){
        bossSkullFlame_spr1 = 0;
    }else if(data->state == 1){
        bossSkullFlame_spr2 = 0;
    }
}