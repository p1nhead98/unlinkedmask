#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 crusher_l_blink[] = {2, 0, 1};
const UINT8 crusher_l_idle[] = {1, 0};
extern UINT8 current_level;

void crusherLeftSound(){
    PlayFx(CHANNEL_1, 15, 0x34, 0xbf, 0xf1, 0xee, 0x82);
    PlayFx(CHANNEL_4, 15, 0x3b, 0xf1, 0x30, 0x80);
}

void crusherLeftCSound(){
    PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
}

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    data->state = 0;
    data->counter = 50;
    data->accel_y = 0;
    THIS->lim_x = 400;
    THIS->lim_y = 80;
    THIS->x += 7;
    if(THIS->x < 432 && current_level == 28){
        data->initial_x = THIS->x = 504;
    }else if (THIS->x > 440 && THIS->x < 680 && current_level == 28){
        THIS->mirror = V_MIRROR;
        data->initial_x = THIS->x = 536;
    }else if(THIS->x < 104 && current_level == 29){
        THIS->mirror = V_MIRROR;
    }else if(THIS->x > 105 && THIS->x < 864 && current_level == 29){
        data->initial_x = THIS->x = 272;
    }else if(THIS->x > 904 && current_level == 29){
        data->initial_y = THIS->y = 72;
        data->initial_x = THIS->x = 1016;
    }else if(current_level == 30){
        if(THIS->x < 880){
            THIS->mirror = V_MIRROR;
        }else{
            data->initial_x = THIS->x = 1072;
        }
    }
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
    
            if(current_level == 27){
                if(scroll_target->x > 1176 && scroll_target->x < 1273){
                // if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 95))  ){
                    data->state = 1;
                    crusherLeftSound();
                    SetSpriteAnim(THIS, crusher_l_blink, 20);
                }
            }else if (current_level == 28){
                if(THIS->x < 513){
                    if(  ((THIS->y + 5) > scroll_target->y) && (THIS->x > scroll_target->x)  ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else if (THIS->x > 936 && THIS->x < 1048){
                    if( (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 95)) ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else{
                    if(  ((THIS->y + 5) > scroll_target->y) && (THIS->x + 15 < scroll_target->x) ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }
            }else if( current_level == 29 ){
                if(THIS->x < 145){
                    if(  (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 38)) && ((THIS->y - 24 ) < scroll_target->y ) ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else if(THIS->x > 904){
                    if( ((scroll_target->x > 864) && (scroll_target->x <  (THIS->x + 3)))  ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else{
                    if( ((scroll_target->x > 128) && (scroll_target->x <  (THIS->x + 3))) && ((THIS->y - 40 ) < scroll_target->y ) ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }
               
            }else if(current_level == 30){
                if(THIS->x < 728){
                    if( ((THIS->y + 5) > scroll_target->y) && (THIS->x + 16 < scroll_target->x) ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else{
                    if( ((scroll_target->x > 880) && (scroll_target->x <  (THIS->x)))  ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                
                }
            }
            
        
            
        break;
        case 1:
        if(current_level == 28 && THIS->x > 520 && THIS->x < 656){
            if(TranslateSprite(THIS, 4 << delta_time, 0)){
                crusherLeftCSound();
                data->state = 2;
                data->counter = 50;
            }
        }else if(THIS->x < 145 && current_level == 29){
            if(TranslateSprite(THIS, 4 << delta_time, 0)){
                crusherLeftCSound();
                data->state = 2;
                data->counter = 50;
            }
        }else if (THIS->x < 703 && current_level == 30) {
            if(TranslateSprite(THIS, 4 << delta_time, 0)){
                crusherLeftCSound();
                data->state = 2;
                data->counter = 50;
            }
        }else if (THIS->x > 703 && current_level == 30) {
            if(TranslateSprite(THIS, -4 << delta_time, 0)){
                crusherLeftCSound();
                data->state = 2;
                data->counter = 10;
            }
        }else{
            if(TranslateSprite(THIS, -4 << delta_time , 0)){
                crusherLeftCSound();
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
            if(current_level == 28 && THIS->x > 520 && THIS->x < 656){
                if(THIS->x > data->initial_x){
                    TranslateSprite(THIS, -1 << delta_time, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }else if(THIS->x < 145 && current_level == 29){
                if(THIS->x > data->initial_x){
                    TranslateSprite(THIS, -1 << delta_time, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }else if(current_level == 30){
                if(THIS->x < 704){
                    if(THIS->x > data->initial_x){
                        TranslateSprite(THIS, -1 << delta_time, 0);
                    }else{
                        data->state = 0;
                        SetSpriteAnim(THIS, crusher_l_idle, 20);
                    }
                }else if(THIS->x > 704){
                    if(THIS->x < data->initial_x){
                        TranslateSprite(THIS, 1 << delta_time, 0);
                    }else{
                        data->state = 0;
                        SetSpriteAnim(THIS, crusher_l_idle, 20);
                    }
                }
            }else{
                if(THIS->x < data->initial_x){
                    TranslateSprite(THIS, 1 << delta_time, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }
        break;
    }
}

void DESTROY()
{
}