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

const UINT8 warning_anim[] = {4, 0, 1, 2, 2};
extern Sprite* warning_spr;
extern Sprite* warning_spr2;

void wrnSound(){
    PlayFx(CHANNEL_1, 10, 0x2c, 0xbf, 0xf1, 0x9e, 0x87);
    // PlayFx(CHANNEL_2, 3, 0x81, 0xf1, 0x37, 0x87);

}
void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, warning_anim, 30);
    data->state = 3;
    data->counter = 0;
    THIS->lim_x = 33;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch(data->state){
        case 0:
        if (THIS->anim_frame == 1 || THIS->anim_frame == 3)
        {
            if(data->counter == 0){
                THIS->x-=16;
                wrnSound();
                data->counter = 1;
            }
            
        }else{
            if(data->counter == 1){
                THIS->x-=16;
                wrnSound();
                data->counter = 0;
            }
        }
        
            
            break;
        case 1:
            if (THIS->anim_frame == 1 || THIS->anim_frame == 3)
            {
                if(data->counter == 0){
                    THIS->x+=16;
                    wrnSound();
                    data->counter = 1;
                }
                
            }else{
                if(data->counter == 1){
                    THIS->x+=16;
                    wrnSound();
                    data->counter = 0;
                }
            }
            break;
        case 2:
            if (THIS->anim_frame == 1 || THIS->anim_frame == 3)
            {
                if(data->counter == 0){
                    THIS->y+=16;
                    wrnSound();
                    data->counter = 1;
                }
                
            }else{
                if(data->counter == 1){
                    THIS->y+=16;
                    wrnSound();
                    data->counter = 0;
                }
            }
            break;
        case 3:
            if (THIS->anim_frame == 1 || THIS->anim_frame == 3)
            {
                if(data->counter == 0){
                    THIS->y-=16;
                    wrnSound();
                    data->counter = 1;
                }
                
            }else{
                if(data->counter == 1){
                    THIS->y-=16;
                    wrnSound();
                    data->counter = 0;
                }
            }
            break;
    }
}

void DESTROY()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
        warning_spr = 0;
        warning_spr2 = 0;
    
}