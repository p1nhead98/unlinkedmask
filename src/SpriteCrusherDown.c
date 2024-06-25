#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 crusher_blink[] = {2, 0, 1};
const UINT8 crusher_idle[] = {1, 0};
extern UINT8 current_level;
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
    THIS->x += 7;
    data->state = 0;
    if(current_level == 28){
        if(THIS->x > 768 && THIS->x < 840){
            THIS->y -= 24;
        }else if(THIS->x > 1080 && THIS->x < 1136){
            THIS->y -= 8;
            THIS->x += 8;
        }else if(THIS->x > 1136 && THIS->x < 1192){
            THIS->x += 8;
            THIS->lim_y = 150;
            THIS->y -= 16;
        }else if(THIS->x > 1192){
            THIS->y+=32;
        }
    }else if(current_level == 26){
        if(THIS->x > 128 && THIS->x < 200){
            THIS->mirror = H_MIRROR;
        }
    }
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
        if(current_level == 26 && THIS->x > 128 && THIS->x < 200){
                if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 40))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                }
        }else if(current_level == 26 && THIS->x > 288 && THIS->x < 320){
            if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 80))  ){
                data->state = 1;
                SetSpriteAnim(THIS, crusher_blink, 20);
            }
        }else if(current_level == 28){
            if(THIS->x < 384){
                if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 34))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                }
            }else if(THIS->x > 1192){
               if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 35))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                } 
            }else{
                if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 35))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                }
            }

        }else{
            if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 55))  ){
                data->state = 1;
                SetSpriteAnim(THIS, crusher_blink, 20);
            }
        }
            
        break;
        case 1:
        if(current_level == 28){
            if(THIS->x > 1192){
                if(TranslateSprite(THIS, 0, -4 << delta_time)){
                    data->state = 2;
                    data->counter = 50;
                }
            }else{
                if(TranslateSprite(THIS, 0, 4 << delta_time)){
                    data->state = 2;
                    data->counter = 50;
                } 
            }
        }else if(current_level == 26 && THIS->x > 128 && THIS->x < 200){
          
            if(TranslateSprite(THIS, 0, -4 << delta_time)){
                data->state = 2;
                data->counter = 50;
            }
            
        }else{ 
            if(TranslateSprite(THIS, 0, 4 << delta_time)){
                data->state = 2;
                data->counter = 50;
            }
        }
            
        break;
        case 2:
            if(--data->counter == 0){
                data->state = 3;
            }
        break;
        case 3:
            if(THIS->y > data->initial_y){
                TranslateSprite(THIS, 0, -1);
            }else{
                data->state = 0;
                SetSpriteAnim(THIS, crusher_idle, 20);
            }
        break;
    }
}

void DESTROY()
{
}