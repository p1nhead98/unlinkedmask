#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 crusher_u_blink[] = {2, 0, 1};
const UINT8 crusher_u_idle[] = {1, 0};
void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    data->state = 0;
    data->counter = 50;
    data->accel_y = 0;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    data->state = 0;
    THIS->x += 7;
    THIS->mirror = H_MIRROR;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
            if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 40), 55))  ){
                data->state = 1;
                SetSpriteAnim(THIS, crusher_u_blink, 20);
            }
        break;
        case 1:
        if(TranslateSprite(THIS, 0, -4)){
            data->state = 2;
            data->counter = 50;
        }
            
        break;
        case 2:
            if(--data->counter == 0){
                data->state = 3;
            }
        break;
        case 3:
            if(THIS->y > data->initial_y){
                TranslateSprite(THIS, 0, 1);
            }else{
                data->state = 0;
                SetSpriteAnim(THIS, crusher_u_idle, 20);
            }
        break;
    }
}

void DESTROY()
{
}