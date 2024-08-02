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

const UINT8 skull_flame_anim[] = {4, 0, 1, 2, 3};
extern Sprite* bossSkullFlame_spr1;
extern Sprite* bossSkullFlame_spr2;

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, skull_flame_anim, 35);
    data->state = 0;

    data->counter = 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch(data->state){
        case 0:
            if(THIS->anim_frame == 3){

                if(data->counter == 0){
                    THIS->x -= 8;
                    data->counter = 1;
                }
            }else if(THIS->anim_frame == 0){
                if(data->counter == 1){
                    data->counter = 0;
                    PlayFx(CHANNEL_4, 15, 0x3a, 0xe1, 0x01, 0x80);
                }
                
            }
            
            break;
        case 1:
            if(THIS->anim_frame == 3){

                if(data->counter == 0){
                    THIS->x += 8;
                    data->counter = 1;
                }
            }else if(THIS->anim_frame == 0){
                if(data->counter == 1){
                    data->counter = 0;
                    PlayFx(CHANNEL_4, 15, 0x3a, 0x81, 0x01, 0x80);
                }
            }
            // THIS->x++;
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